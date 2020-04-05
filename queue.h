#ifndef WORD_C2_QUEUE_H
#define WORD_C2_QUEUE_H
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

class m_queue{
private:
    std::deque<std::vector<std::string>*> *queue_text;
    std::deque<std::map<std::string, int>*> *queue_dicts;
    mutable std::mutex mutex_text;
    mutable std::mutex mutex_dicts;
    mutable std::mutex mutex_threads;
    std::condition_variable cv;
    bool will_be_push_dicts;

    int am_of_active_dicts;
    int am_of_active_text;
    // int am_of_threads_dicts;
    int am_of_threads_text;
    int am_threads;
    void merge_for_one_thread();
    bool can_make_thread();


    void count_part_words();
    void start_threads();
    std::vector<std::thread> vector_of_threads;

    bool finish;




public:
    m_queue(int threads_count);
    void change_working_th_dicts(int value);
    void change_working_th_text(int value);
    void kill_th_text();
    bool will_be_push_text;
    // void add_returning_dict();
    // void sub_returning_dict();

    // void add_working_th_dicts();
    // void sub_working_th_dicts();

    // void add_working_th_text();
    // void sub_working_th_text();

    // void will_be_more_data_dicts();
    // void wont_be_more_data_dicts();

    // void will_be_more_data_text();
    // void wont_be_more_data_text();

    void push_dict(std::map<std::string, int>* elem);
    std::vector<std::map<std::string, int>*> *pop_d(int amount);

    void push_text(std::vector<std::string>* elem);
    std::vector<std::string>* pop_t();

    std::map<std::string, int>* get_res();

    ~m_queue();
};


#endif //WORD_C2_QUEUE_H
