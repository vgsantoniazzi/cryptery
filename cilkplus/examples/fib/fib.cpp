/*
  Copyright (C) 2012 Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
  * Neither the name of Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * fib.cpp
 *
 * Time how long it takes to calculate a Fibonacci number. See
 * http://en.wikipedia.org/wiki/Fibonacci_number for information about the
 * Fibonacci sequence. This application demonstrates the use of the cilk_spawn
 * and cilk_sync keywords.
 *
 * This program takes a single parameter to specify the number of workers to
 * be used in the calculation. If not specified, Intel Cilk Plus will query
 * the operating system to determine the number of cores on the system and use
 * that many workers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#ifdef _WIN32
// Define cilk_getticks and cilk_ticks_to_seconds for Windows
#include <Windows.h>

static inline unsigned long long cilk_getticks()
{
    // Fetch number of milliseconds that have elapsed sin the system started
     return GetTickCount();
}

static inline double cilk_ticks_to_seconds(unsigned long long ticks)
{
     return ticks * 1.0e-3;
}
#else
// Define cilk_getticks and cilk_ticks_to_seconds for Unix-style operating systems
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

int fib(int n)
{
    if (n < 2)
        return n;
    int x = cilk_spawn fib(n-1);
    int y = fib(n-2);
    cilk_sync;
    return x + y;
}

int main(int argc, char *argv[])
{
    // Fibonacci number to be calculated.  39 is big enough to take a
    // reasonable amount of time
    int n = 39;

    // If we've got a parameter, assume it's the number of workers to be used
    if (argc > 1)
    {
        // Values less than 1, or parameters that aren't numbers aren't allowed
        if (atoi(argv[1]) < 1)
        {
            printf("Usage: fib [workers]\n");
            return 1;
        }

        // Set the number of workers to be used
        __cilkrts_set_param("nworkers", argv[1]);
    }

    // Time how long it takes to calculate the nth Fibonacci number
    unsigned long long start = cilk_getticks();
    int result = fib(n);
    unsigned long long end = cilk_getticks();

    // Display our results
    double duration = cilk_ticks_to_seconds(end - start);
    printf("Fibonacci number #%d is %d.\n", n, result);
    printf("Calculated in %.3f seconds using %d workers.\n",
           duration, __cilkrts_get_nworkers());

    return 0;
}
