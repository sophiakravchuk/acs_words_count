#include "time_measurement.h"

std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
// Gets solution from https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp
void TemporaryFunction2 ()
{
    std::chrono::duration<long, std::ratio<1l, 1000000000l> >  d{};
    to_us(d);
}