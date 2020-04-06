#include "file_of_vecs.h"


std::vector<std::vector<std::string>*>* chars_to_vecs(char* buffer, int am_of_vecs)
{
    membuf sbuf(buffer, buffer + sizeof(buffer));
    std::istream in(&sbuf);
    std::string word;
    auto all_vec = new std::vector<std::vector<std::string>*>();
    for (int i = 0; i < am_of_vecs; i ++) {
        auto new_vec = new std::vector<std::string>();
        all_vec->push_back(new_vec);
    }

    int numb = 0;
    while (in) {
        in >> word;
        (*all_vec)[numb % am_of_vecs]->push_back(word);
        numb++;
    }
    return all_vec;

}
