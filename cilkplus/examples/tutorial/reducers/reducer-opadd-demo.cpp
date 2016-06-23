/*
 * reducer-opadd-demo.cpp
 *
 * This program demonstrates using an opadd reducer to sum a series of values
 * in parallel.
 */

#include <cstdio>
#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

// stall() will pause 1/10 of a second, which should be long enough for
// the continuation to have been stolen
#ifdef _MSC_VER
#include <windows.h>
void stall()
{
    Sleep(100);         // 100 milliseconds = .1 second
}
#else
#include <unistd.h>
void stall()
{
    usleep(100 * 1000); // 100 * 1000 microseconds = .1 second
}
#endif

int main(int argc, char **argv)
{
    // Sum the numbers 1-1000 serially
    int serial_sum = 0;
    for(int i = 0; i < 1000; i++)
	serial_sum += i;
    printf("Serial sum: %d\n", serial_sum);

    // Sum the numbers 1-1000 in parallel, adding a pause to allow the
    // continuation to be stolen
    cilk::reducer_opadd<int> parallel_sum;
    cilk_for(int i = 0; i < 1000; i++)
    {
	if (0 == i % 10)
	    stall();
	parallel_sum += i;
    }
    printf("Parallel sum: %d\n", parallel_sum.get_value());

    assert(serial_sum == parallel_sum.get_value());
    return 0;
}
