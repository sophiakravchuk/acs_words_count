//
// Created by student on 04.04.20.
//

#ifndef WORD_C2_THREADS_MERGE_H
#define WORD_C2_THREADS_MERGE_H
#include <thread>
#include <map>
#include "queue.h"

void merge_for_one_thread(m_queue *queue);
int merge_maps(m_queue *queue, int am_threads);

#endif //WORD_C2_THREADS_MERGE_H
