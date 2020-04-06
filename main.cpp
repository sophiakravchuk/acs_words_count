#include <iostream>
#include <map>
#include "queue.h"
#include "time_measurement.h"
#include "file_of_vecs.h"
//#include "libzip/zip.h"
#include <zip.h>

//
//
////std::vector<std::string> *create_vecs(int n){
//    auto *result = new std::vector<std::string>();
//    for(int i = 0; i < n; i++){
//        std::string str = std::to_string(i);
//        (*result).push_back(str);
//    }
//    return result;
//}
//
//std::map<std::string, int> * two_main(int am_threads){
//    int len = 500;
//    int vects = 200;
//
//    std::vector<std::string> *d1 = create_vecs(len);
//    auto start_time = get_current_time_fenced();
//
//    auto *que = new m_queue(am_threads);
//    for (auto i = 0; i < vects - 1; i++) {
//        auto new_dict = new std::vector<std::string>(*d1);
//        que->push_text(new_dict);
//    }
//    que->push_text(d1);
//    que->will_be_push_text = false;
//    std::cout << "pushed" << std::endl;
//    auto res =  que->get_res();
//    auto total_time = get_current_time_fenced() - start_time;
//    std::cout << "Total time, (am of th "<< am_threads << " ): " << to_us(total_time) << std::endl;
//    return res;
//}

int main() {
    auto start_time = get_current_time_fenced();
    char* file_name = "data.zip";
    char* file_name_in_zip = "text.txt";
    int am_threads = 4;
    //Open the ZIP archive
    int err = 0;
    zip *z = zip_open(file_name, 0, &err);

    //Search for the file of given name
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, file_name_in_zip, 0, &st);

    //Alloc memory for its uncompressed contents
    char *contents = new char[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, file_name_in_zip, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);
    auto total_time = get_current_time_fenced() - start_time;
    std::cout << "Unzip file " << to_us(total_time) << std::endl;
    start_time = get_current_time_fenced();
    auto vecs = chars_to_vecs(contents, 1000);
        delete[] contents;
        m_queue* que = new m_queue(am_threads);
        for (auto vec: (*vecs)){
            que->push_text(vec);
        }
        que->get_res();
    total_time = get_current_time_fenced() - start_time;
    std::cout << "Unzip file " << to_us(total_time) << std::endl;
    return 0;
    }

