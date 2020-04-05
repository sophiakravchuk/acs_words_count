#include <map>
#include <algorithm>
#include <iostream>
#include "queue.h"

m_queue::m_queue(int threads_count) {
    am_threads = threads_count;
    queue_dicts = new std::deque<std::map<std::string, int>*>();
    queue_text = new std::deque<std::vector<std::string>*>();
    am_of_active_dicts = 0;
    am_of_active_text = 0;
    will_be_push_dicts = true;
    will_be_push_text = true;
    am_of_threads_text = threads_count;
    start_threads();
    // am_of_threads_dicts = threads_count;
}

void m_queue::change_working_th_dicts(int value){
    std::unique_lock<std::mutex> mlock(mutex_threads);
    am_of_active_dicts += value;
    mlock.unlock();
}

void m_queue::change_working_th_text(int value){
    std::unique_lock<std::mutex> mlock(mutex_threads);
    am_of_active_text += value;
    mlock.unlock();
}

void m_queue::kill_th_text(){
    std::unique_lock<std::mutex> mlock(mutex_threads);
    am_of_threads_text--;
    if (am_of_threads_text == 0){
        will_be_push_dicts = false;
    }
    mlock.unlock();
}

bool m_queue::can_make_thread(){
    std::unique_lock<std::mutex> mlock(mutex_threads);
    bool res = am_of_active_dicts + am_of_active_text < am_threads;
    mlock.unlock();
    return res;
}

void m_queue::push_text(std::vector<std::string>* elem){
    std::unique_lock<std::mutex> mlock(mutex_text);
    queue_text->push_back(elem);
    mlock.unlock();
    cv.notify_all();
}

void m_queue::push_dict(std::map<std::string, int>* elem){
    std::unique_lock<std::mutex> mlock(mutex_dicts);
    queue_dicts->push_back(elem);
    mlock.unlock();
    cv.notify_all();
}

std::vector<std::map<std::string, int>*> *m_queue::pop_d(int amount){
    std::unique_lock<std::mutex> mlock(mutex_dicts);
    while(true){
        if (queue_dicts->size() <= 1 && !will_be_push_dicts && am_of_active_dicts == 0){
            if(can_make_thread()) {
                cv.notify_all();
            }
            return NULL;
        } else if (queue_dicts->size() <= 1 && (will_be_push_dicts || am_of_active_dicts != 0)) {
            std::cout << "dict sleep" << std::endl;
            cv.wait(mlock);
        }else {
            break;
        }
    }
    std::cout << "dict work" << std::endl;
    auto *result = new std::vector<std::map<std::string, int>*>();
    for (int i = 0; i < amount; i++){
        std::map<std::string, int>* elem = queue_dicts->front();
        queue_dicts->pop_front();
        result->push_back(elem);
    }
    mlock.unlock();
    change_working_th_dicts(1);
    return result;
}

std::vector<std::string>* m_queue::pop_t(){
    std::vector<std::string>* elem;
    while(true){
        std::unique_lock<std::mutex> mlock(mutex_text);
        if(can_make_thread()) {
            if (queue_text->size() <= 0 && !will_be_push_text){
                std::cout << "text dead" << std::endl;
                cv.notify_all();
                mlock.unlock();
                return NULL;
            } else if (queue_text->size() <= 0 && will_be_push_text) {
                std::cout << "text sleep" << std::endl << std::flush;
                cv.wait(mlock);
            }else {
                elem = queue_text->front();
                queue_text->pop_front();
                break;
            }
        }else{
            cv.wait(mlock);
        }
        mlock.unlock();
    }
    change_working_th_text(1);
    return elem;
}

m_queue::~m_queue(){
    delete queue_dicts;
}

void m_queue::merge_for_one_thread(){
    while (true) {
        std::vector<std::map<std::string, int>*> *dicts = pop_d(2);
        if (dicts == NULL || dicts->size() <= 1){
            std::cout << "dict dead" << std::endl;
            break;
        }
        std::map<std::string, int> *dict1 = (*dicts)[0];
        std::map<std::string, int> *dict2 = (*dicts)[1];

        for (auto &x : *dict1) {
            if (dict2->find(x.first) == dict2->end()) {
                (*dict2)[x.first] = x.second;
            } else {
                (*dict2)[x.first] += x.second;
            }
        }
        delete dict1;
        push_dict(dict2);
        change_working_th_dicts(-1);
    }
}

void m_queue::count_part_words() {
    while(true){
        std::vector<std::string>* words_vec = pop_t();
        if (words_vec == NULL){
            kill_th_text();
            std::cout << "text dead" << std::endl;
            break;
        }
        auto result = new std::map<std::string, int>();
        for (std::string& el : (*words_vec)) {
            el.erase (std::remove_if(el.begin (), el.end (), ispunct), el.end ());

            std::transform(el.begin(), el.end(), el.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if ( result->find(el) == result->end() ) {
                result->insert({ el, 1 });
            } else {
                (*result)[el]++;
            }
        }
        push_dict(result);
        change_working_th_text(-1);
    }
}

void m_queue::start_threads(){
    vector_of_threads.reserve(am_threads*2);

    for (int i = 0; i < am_threads; i++) {
        vector_of_threads.emplace_back(std::thread(&m_queue::merge_for_one_thread, this));
    }
    std::cout << "text ready " << am_threads << std::endl;
    for (int i = 0; i < am_threads; i++) {
        vector_of_threads.emplace_back(std::thread(&m_queue::count_part_words, this));
    }
    std::cout << "dict ready " << am_threads << std::endl;
}

std::map<std::string, int>* m_queue::get_res(){
    for (auto &t: vector_of_threads) {
        t.join();
    }
    return queue_dicts->front();
}
