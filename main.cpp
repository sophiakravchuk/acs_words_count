#include <iostream>
#include <map>
#include "queue.h"
#include "time_measurement.h"
#include "file_of_vecs.h"
//#include "libzip/zip.h"
#include <zip.h>


int main() {
    auto start_time = get_current_time_fenced();
    char* file_name = "../data.zip";
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
//        std::cout << (*vec)[0] << std::endl;
        que->push_text(vec);
    }
    que->will_be_push_text = false;
    std::cout << que->get_res() << std::endl;
    total_time = get_current_time_fenced() - start_time;
    std::cout << "Unzip file " << to_us(total_time) << std::endl;
//    que->get_res();
    return 0;
    }

