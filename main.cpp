#include <iostream>
#include <map>
#include "queue.h"

//#include "threads_merge.h"
#include "time_measurement.h"



std::vector<std::string> *create_vecs(int n){
    auto *result = new std::vector<std::string>();
    for(int i = 0; i < n; i++){
        std::string str = std::to_string(i);
        (*result).push_back(str);
    }
    return result;
}

std::map<std::string, int> * two_main(int am_threads){
    int len = 500;
    int vects = 200;

    std::vector<std::string> *d1 = create_vecs(len);
    auto start_time = get_current_time_fenced();

    auto *que = new m_queue(am_threads);
    for (auto i = 0; i < vects - 1; i++) {
        auto new_dict = new std::vector<std::string>(*d1);
        que->push_text(new_dict);
    }
    que->push_text(d1);
    que->will_be_push_text = false;
    std::cout << "pushed" << std::endl;
    auto res =  que->get_res();
    auto total_time = get_current_time_fenced() - start_time;
    std::cout << "Total time, (am of th "<< am_threads << " ): " << to_us(total_time) << std::endl;
    return res;
}

int main() {
    std::map<std::string, int>* a = two_main(4);
//    std::map<std::string, int>* b = two_main(3);
//    std::map<std::string, int>* c = two_main(2);
//    std::map<std::string, int>* d = two_main(1);

    std::cout << a->size() << std::endl;
    std::cout << (*a)["0"] << std::endl;

//    std::cout << b << std::endl;
//    std::cout << c << std::endl;
//    std::cout << d << std::endl;
    return 0;
}
