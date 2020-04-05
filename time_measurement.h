#ifndef WORD_C2_TIME_MEASUREMENT_H
#define WORD_C2_TIME_MEASUREMENT_H
#include <chrono>
#include <atomic>

std::chrono::high_resolution_clock::time_point get_current_time_fenced();

template<class D>
long long to_us(const D& d);

#endif //WORD_C2_TIME_MEASUREMENT_H
