//#include "threads_merge.h"
//
//void merge_for_one_thread(m_queue *queue){
//    while (true) {
//        std::vector<std::map<std::string, int>*> *dicts = queue->pop_d(2);
//        if (dicts == NULL || dicts->size() <= 1){
////            break;
////            std::cout << "I'm Out" << std::endl;
//            break;
//        }
//        queue->add_working_th_dicts();
//        std::map<std::string, int> *dict1 = (*dicts)[0];
//        std::map<std::string, int> *dict2 = (*dicts)[1];
//
//        for (auto &x : *dict1) {
//            if (dict2->find(x.first) == dict2->end()) {
//                (*dict2)[x.first] = x.second;
//            } else {
//                (*dict2)[x.first] += x.second;
//            }
//        }
//        delete dict1;
//        queue->push_dict(dict2);
//        queue->sub_working_th_dicts();
//    }
//}
//
//int merge_maps(m_queue *queue, int am_threads){
//    std::vector<std::thread> vector_of_threads;
//    vector_of_threads.reserve(am_threads);
//
//    for (int i = 0; i < am_threads; i++) {
//        vector_of_threads.emplace_back(std::thread(merge_for_one_thread, queue));
//    }
//    for (auto &t: vector_of_threads) {
//        t.join();
//    }
//    return 0;
//}
