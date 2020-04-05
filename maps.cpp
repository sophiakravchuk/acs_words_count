#include "maps.h"

std::map<std::string, int> *create_dict(int n){
     auto *result = new std::map<std::string, int>();
    for(int i = 0; i <= n; i++){
        std::string str = std::to_string(i);
        (*result)[str] = 1;
    }
    return result;
}


m_queue *make_maps(int am_threads) {
    int n = 50000;
    int dicts = 200;
    std::map<std::string, int> *d1 = create_dict(n);
//    std::vector<std::map<std::string, int>> arr;
//    arr.reserve(dicts);
    auto *que = new m_queue(am_threads);
    for(auto i = 0; i < dicts - 1; i++) {
//        auto new_dict = std::map<std::string, int>(d1);
        auto new_dict = new std::map<std::string, int>(*d1);
        que->push_dict(new_dict);
    }
    que->push_dict(d1);
////
////    d1["aaa"] = 1;
////    d1["bbb"] = 2;
////    d1["ccc"] = 3;
////    d1["ddd"] = 4;
//    std::map<std::string, int> *d2 = create_dict(n);
////    d2["aaa"] = 1;
////    d2["eee"] = 2;
////    d2["ccc"] = 3;
////    d2["fff"] = 4;
//    std::map<std::string, int> *d3 = create_dict(n);
////    d3["vvv"] = 1;
////    d3["eee"] = 2;
////    d3["ccc"] = 3;
////    d3["fff"] = 4;
//    std::map<std::string, int> *d4 = create_dict(n);
////    d4["aaa"] = 1;
////    d4["vvv"] = 2;
////    d4["rrr"] = 3;
////    d4["fff"] = 4;
//    std::map<std::string, int> *d5 = create_dict(n);
////    d5["aaa"] = 1;
////    d5["eee"] = 2;
////    d5["ccc"] = 3;
////    d5["fff"] = 4;
//    std::map<std::string, int> *d6 = create_dict(n);
////    d6["aaa"] = 1;
////    d6["rrr"] = 2;
////    d6["ccc"] = 3;
////    d6["fff"] = 4;
//    std::map<std::string, int> d7 = create_dict(n);
//    std::map<std::string, int> d8 = create_dict(n);
//    d7["aaa"] = 1;
//    d7["eee"] = 2;
//    d7["sss"] = 3;
//    d7["fff"] = 4;
////    std::vector<std::map<std::string, int>> arr = {d1, d2, d3, d4, d5, d6, d7, d8};
////    auto *que = new m_queue<std::map<std::string, int>>();
////    que->push(d1);
////    que->push(d2);
////    que->push(d3);
////    que->push(d4);
////    que->push(d5);
////    que->push(d6);
////    que->push(d7);
////    que->push(d8);
    que->wont_be_more_data_dicts();
//    std::map<std::string, int> p;
//    p["."] = 1;
//    que->set_poison_pill(p);
//    std::map<std::string, int> p;
//    std::string str = ".";
//    p[str] = 1;
//    que->push(p);
    return que;
}


m_queue *make_vec(int am_threads) {
    int n = 50000;
    int dicts = 200;
    std::map<std::string, int> *d1 = create_dict(n);
//    std::vector<std::map<std::string, int>> arr;
//    arr.reserve(dicts);
    auto *que = new m_queue(am_threads);
    for (auto i = 0; i < dicts - 1; i++) {
//        auto new_dict = std::map<std::string, int>(d1);
        auto new_dict = new std::map<std::string, int>(*d1);
        que->push_dict(new_dict);
    }
    que->push_dict(d1);
    return que;
}