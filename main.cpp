#include <iostream>
#include <map>
#include "time_measurement.cpp"
#include "queue.cpp"
#include "maps.cpp"
#include "threads_merge.cpp"

void one_main(int am_threads){
    std::cout << "Creating arrays..." << std::flush;
    auto start_time = get_current_time_fenced();
    m_queue<std::map<std::string, int>*> *queue = make_maps();
    auto total_time = get_current_time_fenced() - start_time;
    std::cout << " Done " << to_us(total_time) << std::endl<< std::flush;
    start_time = get_current_time_fenced();

    merge_maps(queue, am_threads);

    auto finish_time = get_current_time_fenced();
    total_time = finish_time - start_time;

    std::cout << "Total time, (am of th "<< am_threads << " ): " << to_us(total_time) << std::endl;
//
//    auto d1 = queue->pop();
//    for(const auto& x: d1){
//        std::cout << x.first << x.second << std::endl;
//    }
//    std::cout << std::endl;
//    auto d2 = queue->pop();
//    for(const auto& x: d2){
//        std::cout << x.first << x.second << std::endl;
//    }
}


int main() {
    one_main(4);
    one_main(3);
    one_main(2);
    one_main(1);


    return 0;
}
