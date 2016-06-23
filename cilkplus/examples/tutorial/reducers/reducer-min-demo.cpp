/*
 * reducer-min-demo
 *
 * This example demonstrates using reducer_min.  The example fills an array
 * of chars with the letters A-Z, allowing you specify an offset so you can
 * control which element has the letter 'A'.  It then uses a reducer to find
 * the letter with the minimum value ('A').
 *
 * If offset + 26 overflows unsigned, this probably doesn't work.  Use small
 * values.
 */

#include <cstdio>
#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_min.h>

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

void reducer_min_test(unsigned offset)
{
    char a[26];
    // Creates an array a of 'A' through 'Z', with
    // 'A' == a[offset % 26].
    for (unsigned i = 0; i < 26u; ++i)
    {
        a[(i + offset) % 26] = 'A' + i;
    }

    // Construct the min reducer.  The reducer starts as invalid, so it is
    // unnecessary to set the initial value.
    cilk::reducer_min<char> best;

    // Print out each character, calculate the minimum value and it's index,
    // and pause 1/10 second so that stealing will occur.  We pause to
    // demonstrate that the different workers are interleaving their results
    cilk_for(unsigned i = 0; i < 26; ++i)
    {
        printf("a[%u] = %c\n", i, a[i]);
        best.calc_min(a[i]);
        stall();
    }

    // Print out the result
    printf("Minimum value = %c\n",
           best.get_value());
}

int main(int argc, char* argv[])
{
    // Use a default offset of 15, but allow the user to override. Offset
    // must be a positive value.
    int offset = 15;
    if (argc > 1)
        offset = atoi(argv[1]);
    assert(offset >= 0);

    // Use 4 workers so stealing will occur, even on a single core system
    __cilkrts_set_param("nworkers", "4");

    // Run the test
    printf("Testing with offset = %d\n", offset);
    reducer_min_test(offset);
    return 0;
}
