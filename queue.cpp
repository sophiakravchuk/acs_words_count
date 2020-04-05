
#include <map>
#include <algorithm>
#include <iostream>
#include "queue.h"



m_queue::m_queue(int threads_count) {
    am_threads = threads_count;
    queue_dicts = new std::deque<std::map<std::string, int>*>();
    queue_text = new std::deque<std::vector<std::string>*>();
    am_of_returning_dicts = 0;
    am_of_working_thr_text = 0;
    will_be_push_dicts = true;
    will_be_push_text = true;
    start_threads();
}

void m_queue::add_returning_dict(){
    am_of_returning_dicts++;
}

void m_queue::sub_returning_dict(){
    am_of_returning_dicts--;
}

void m_queue::add_working_th_dicts(){
    am_of_working_thr_dicts++;
}

void m_queue::sub_working_th_dicts(){
    am_of_working_thr_dicts--;
}

void m_queue::add_working_th_text(){
    am_of_working_thr_text++;
}

void m_queue::sub_working_th_text(){
    am_of_working_thr_text--;
    if (am_of_working_thr_text == 0){
        wont_be_more_data_dicts();
    }
}

void m_queue::will_be_more_data_dicts(){
    will_be_push_dicts = true;
}

void m_queue::wont_be_more_data_dicts(){
    will_be_push_dicts = false;
}

void m_queue::will_be_more_data_text(){
    will_be_push_text = true;
}

void m_queue::wont_be_more_data_text(){
    will_be_push_text = false;
}

size_t m_queue::get_size_dicts() const{
    std::unique_lock<std::mutex> mlock(mutex_dicts);
    auto result = queue_dicts->size();
    mlock.unlock();
    return result;
}

size_t m_queue::get_size_text() const{
    std::unique_lock<std::mutex> mlock(mutex_text);
    auto result = queue_text->size();
    mlock.unlock();
    return result;
}

void m_queue::push_text(std::vector<std::string>* elem){
    std::unique_lock<std::mutex> mlock(mutex_text);
    queue_text->push_back(elem);
    mlock.unlock();
    if(can_make_thread_text()){
        std::cout << "text awake" << std::endl;
        cv_text.notify_one();
        add_working_th_text();
    }
}

void m_queue::push_dict(std::map<std::string, int>* elem){
    std::unique_lock<std::mutex> mlock(mutex_dicts);
    queue_dicts->push_back(elem);
    mlock.unlock();
    if(can_make_thread_dict()) {
        cv_dicts.notify_one();
        add_working_th_dicts();
    }
}

bool m_queue::can_make_thread(){
    bool res = am_of_returning_dicts + am_of_working_thr_text < am_threads;
    return res;
}
//
//bool m_queue::can_make_thread_text(){
//    std::unique_lock<std::mutex> mlockt(mutex_text);
//    std::unique_lock<std::mutex> mlockd(mutex_dicts);
//    bool res = can_make_thread() && am_of_working_thr_text < am_threads;
//    mlockd.unlock();
//    mlockt.unlock();
//    return res;
//}
//
//bool m_queue::can_make_thread_dict(){
//    std::unique_lock<std::mutex> mlockt(mutex_text);
//    std::unique_lock<std::mutex> mlockd(mutex_dicts);
//    bool res = can_make_thread() && am_of_returning_dicts < am_threads;
//    mlockd.unlock();
//    mlockt.unlock();
//    return res;
//}

std::vector<std::map<std::string, int>*> *m_queue::pop_d(int amount){
    std::unique_lock<std::mutex> mlock(mutex_dicts);
    while(true){
        if (queue_dicts->size() <= 1 && !will_be_push_dicts && am_of_returning_dicts == 0){
//                result->push_back(poison_pill);
            if(can_make_thread_dict()) {
                cv_dicts.notify_all();
            }
            return NULL;
//                break;
        } else if (queue_dicts->size() <= 1 && (will_be_push_dicts || am_of_returning_dicts != 0)) {
//                cv_dicts.wait(mlock, [this]() { return queue_dicts.size() > 1;});
            std::cout << "dict sleep" << std::endl;
            cv_dicts.wait(mlock);
        }else {
            break;
        }
    }

    auto *result = new std::vector<std::map<std::string, int>*>();
    for (int i = 0; i < amount; i++){
        std::map<std::string, int>* elem = queue_dicts->front();
        queue_dicts->pop_front();
        result->push_back(elem);
    }

    mlock.unlock();
    return result;
}

std::vector<std::string>* m_queue::pop_t(){
    while(true){
        if(can_make_thread()){
            std::unique_lock<std::mutex> mlock(mutex_text);
            if(can_make_thread()) {
                add_working_th_text();
            }
        }
        if (queue_text->size() <= 1 && !will_be_push_text){
            if(can_make_thread_text()){
                std::cout << "text dead" << std::endl;
                cv_text.notify_all();
            }
            return NULL;
        } else if (queue_text->size() <= 1 && will_be_push_text) {
            std::cout << "text sleep" << std::endl;
            cv_text.wait(mlock);
        }else {
            break;
        }
        std::vector<std::string>* elem = queue_text->front();
        queue_text->pop_front();

        mlock.unlock();
    }
    std::vector<std::string>* elem = queue_text->front();
    queue_text->pop_front();

    mlock.unlock();
    return elem;
}

m_queue::~m_queue(){
    delete queue_dicts;
}

void m_queue::merge_for_one_thread(){
    while (true) {
        std::vector<std::map<std::string, int>*> *dicts = pop_d(2);
        if (dicts == NULL || dicts->size() <= 1){
//            break;
//            std::cout << "I'm Out" << std::endl;
            std::cout << "dict dead" << std::endl;
            sub_working_th_dicts();
            break;
        }
        add_returning_dict();
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
        sub_returning_dict();
    }
}

void m_queue::count_part_words() {
    while(true){
        std::vector<std::string>* words_vec = pop_t();
        if (words_vec == NULL){
            sub_working_th_text();
            std::cout << "text dead" << std::endl;
            break;
        }
        add_working_th_text();
        auto result = new std::map<std::string, int>();
        for (std::string& el : (*words_vec)) {
            el.erase (std::remove_if(el.begin (), el.end (), ispunct), el.end ());
    //        std::cout << el << std::endl;

            std::transform(el.begin(), el.end(), el.begin(),
                           [](unsigned char c){ return std::tolower(c); });
    //        std::cout << el << std::endl;
            if ( result->find(el) == result->end() ) {
                result->insert({ el, 1 });
            } else {
                (*result)[el]++;
            }
        }
        push_dict(result);
        sub_working_th_text();
    }
//    delete result;
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

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
// Gets solution from https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp
//void TemporaryFunction ()
//{
//    m_queue TempObj(4);
//    TempObj.push_dict(NULL);
//    TempObj.push_text(NULL);
//    std::vector<std::map<std::string, int>*>* el1 = TempObj.pop_d(2);
//    std::vector<std::string>* el2 = TempObj.pop_t();
//
//    TempObj.will_be_more_data_dicts();
//    TempObj.wont_be_more_data_dicts();
//    TempObj.will_be_more_data_text();
//    TempObj.wont_be_more_data_text();
//
//    TempObj.add_working_th_dicts();
//    TempObj.sub_working_th_dicts();
//
//    TempObj.add_working_th_text();
//    TempObj.sub_working_th_text();
//
//    TempObj.get_size_dicts();
//    TempObj.get_size_text();
//}
