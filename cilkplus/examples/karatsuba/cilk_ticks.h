/*
 * cilk_ticks.h
 *
 * Calculate elapsed time in "ticks". A "tick" is a 64-bit integer. On
 * Windows, a "tick" is counted in milliseconds since the system booted.
 * On Unix-derived systems, a "tick" is counted in microseconds since
 * 1-Jan-1970.
 *
 * For both systems, cilk_ticks_to_seconds() converts from ticks to seconds.
 */

#ifdef _WIN32
#include <Windows.h>

static inline unsigned long long cilk_getticks()
{
    // Fetch number of milliseconds that have elapsed since the system started
     return GetTickCount();
}

static inline double cilk_ticks_to_seconds(unsigned long long ticks)
{
     return ticks * 1.0e-3;
}
#endif

#if defined __unix__ || defined __APPLE__
#include <time.h>
#include <sys/time.h>

static inline unsigned long long cilk_getticks()
{
     struct timeval t;
     gettimeofday(&t, 0);
     return t.tv_sec * 1000000ULL + t.tv_usec;
}

static inline double cilk_ticks_to_seconds(unsigned long long ticks)
{
     return ticks * 1.0e-6;
}
#endif
