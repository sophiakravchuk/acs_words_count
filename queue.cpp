#include <queue>
#include <condition_variable>

template <typename T>
class m_queue{
private:
    std::deque<T> *queue_internal;
    mutable std::mutex m_m;
    std::condition_variable cv_m;
    T poison_pill;
    bool will_be_push = true;

public:
    m_queue(){
        queue_internal = new std::deque<T>();
        am_of_returning_dicts = 0;
    };
    int am_of_returning_dicts;
    void set_poison_pill(T pp){
        poison_pill = pp;
    }

    void will_be_more_data(){
        will_be_push = true;
    }
    void wont_be_more_data(){
        will_be_push = false;
    }

    void push(T elem){
        std::unique_lock<std::mutex> mlock(m_m);
        queue_internal->push_back(elem);
        mlock.unlock();
        cv_m.notify_one();
    }

    std::vector<T> *pop(int amount=1){
        std::unique_lock<std::mutex> mlock(m_m);
        while(true){
            if (queue_internal->size() <= 1 && !will_be_push && am_of_returning_dicts == 0){
//                result->push_back(poison_pill);
                cv_m.notify_all();
                return NULL;
//                break;
            } else if (queue_internal->size() <= 1 && (will_be_push || am_of_returning_dicts != 0)) {
//                cv_m.wait(mlock, [this]() { return queue_internal.size() > 1;});
                cv_m.wait(mlock);
            }else {
                break;
            }
        }

        std::vector<T> *result = new std::vector<T>();
        for (int i = 0; i < amount; i++){
            T elem = queue_internal->front();
            queue_internal->pop_front();
            result->push_back(elem);
        }

        mlock.unlock();
        return result;
    }

    size_t get_size() const {
        std::unique_lock<std::mutex> mlock(m_m);
        auto result = queue_internal->size();
        mlock.unlock();
        return result;
    }
};
