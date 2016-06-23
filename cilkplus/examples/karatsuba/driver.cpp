/*
 * driver.cpp
 *
 * Based on the implementation of the Karatsuba algorithm for polynomial
 * multiplication from "Structure Parallel Programming" by Michael McCool,
 * Arch Robison and James Reinders. The original source code is available
 * from http://parallelbook.com/downloads
 *
 * Information on the Karatsuba algorithm can be found at Wikipedia:
 * http://en.wikipedia.org/wiki/Karatsuba_algorithm
 */

#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cilk/cilk_api.h>

#include "karatsuba.h"
#include "cilk_ticks.h"

// Minimum time for a trial to run
const double MinTime = 10.0;

// Degree of the polynomials we're dealing with
const size_t nMax = 10000;

/*
 * Fill an array with random numbers
 */
static void FillRandom (T x[], size_t n)
{
    const unsigned Radix = 10;
    for (size_t k=0; k<n; ++k)
        x[k] = std::rand() % Radix;
}

/*
 * Test the implementations of the Karatsuba alorithm. The result of the serial
 * implementation is compared to the results of the other three implementations.
 * If they all match, we assume that they're correct.
 */
static void TestKaratsuba()
{
    for (size_t trial=0; trial<4; ++trial)
    {
        for (size_t n=1; n<nMax; n*=3)
        {
            T x[nMax];
            T y[nMax];
            T z[2][2*nMax];

            FillRandom(x,n);
            FillRandom(y,n);

            // Start with the serial implementation
            karatsuba_serial(z[0],x,y,n);

            // Compare the serial implementation against the parallel, vectorized
            // implementation
            karatsuba_parallel_vectorized(z[1],x,y,n);
            for (size_t i=0; i<2*n-1; ++i)
                assert(z[0][i]==z[1][i]);

            // Compare the serial implementation against the vectorized implementation
            karatsuba_vectorized(z[1],x,y,n);
            for (size_t i=0; i<2*n-1; ++i)
                assert(z[0][i]==z[1][i]);

            // Compare the serial implementation against the parallel implementation
            karatsuba_parallel(z[1],x,y,n);
            for (size_t i=0; i<2*n-1; ++i)
                assert(z[0][i]==z[1][i]);
        }
    }
}

/*
 * Run a function and report how long it took, as well the speedup for
 * subsequent runs over the first run
 */
typedef void (*Routine)( T c[], const T a[], const T b[], size_t n );

static void TimeRoutine(Routine r, const char* what)
{
    // First call is used to choose how many iterations to time.
    static int TrialCount;
    bool firstCall = TrialCount==0;
    static double tBase;
    double t;

    T x[nMax];
    T y[nMax];
    T z[2*nMax];

    FillRandom(x,nMax);
    FillRandom(y,nMax);

    if (firstCall)
        TrialCount=1;

    for(;;)
    {
        unsigned long long t0 = cilk_getticks();
        for (int i=0; i<TrialCount; ++i)
            (*r)(z,x,y,nMax);
        unsigned long long t1 = cilk_getticks();
        t = cilk_ticks_to_seconds(t1-t0);
        if (!firstCall || (t>=MinTime))
            break;
        // Double the number of iterations
        TrialCount*=2;
    }

    if (firstCall)
    {
        // Print table caption and heading
        printf("Timing %d multiplications of %lu-degree polynomials\n\n",TrialCount,(unsigned long)nMax);
        printf("%20s  %s  %s\n","Version","Time", "Speedup");
        tBase = t;
    }
    std::printf("%20s %6.3f %5.2f x\n",what,t,tBase/t);
}

/*
 * Test for karatsuba routines
 */
int main (int argc, char* argv[])
{
    std::srand(2);

    // Test for correctness. If the implementations give different results,
    // the test function will not return.
    printf("Testing Karatsuba implementations... ");
    TestKaratsuba();
    printf("Validated\n");

    // Test speed.  The correctness tests are assumed to have warmed up the runtime.
    printf("\nStarting speed tests. Parallel runs will use %d threads...\n\n",
           __cilkrts_get_nworkers());

    TimeRoutine(karatsuba_serial, "Serial");
    TimeRoutine(karatsuba_vectorized, "Vectorized");
    TimeRoutine(karatsuba_parallel, "Parallel");
    TimeRoutine(karatsuba_parallel_vectorized, "Parallel/Vectorized");

    return 0;
}
