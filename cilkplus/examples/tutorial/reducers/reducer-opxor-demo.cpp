/*
 * reducer-opxor-demo.cpp
 *
 * This example demonstrates using an opxor reducer to compute a bitmask in
 * parallel.  It initializes the result to 0, and then XORs in a mask with
 * all of the bits below the Kth bit set,  both in a serial loop and in
 * parallel.  The results are displayed and compared.
 */

#include <cstdio>
#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_opxor.h>

// This test starts with a 64-bit mask of all 0's, and alternately sets
// K bits
void reducer_opxor_test(unsigned K)
{
    // Alternate setting sets of bits that are K bits apart
    uint64_t serial_ans = 0;
    for (int i = 0; i < 64; i+= K)
    {
        uint64_t i_mask = (1ULL << i) - 1;
        serial_ans ^= i_mask;
    }
    printf("Serial result:   0x%lX\n", serial_ans);

    // Do the same operation in parallel, in a cilk_for loop.
    cilk::reducer_opxor<uint64_t> parallel_ans(0);
    cilk_for(int i = 0; i < 64; i+= K)
    {
        uint64_t i_mask = (1ULL << i) - 1;
        parallel_ans ^= i_mask;
    }
    printf("Parallel result: 0x%lX\n", parallel_ans.get_value());

    assert(serial_ans == parallel_ans.get_value());
}

int main(int argc, char* argv[])
{
    // Default argument for spacing.
    int spacing = 4;

    // Read in spacing from command line, if one is provided.
    if (argc > 1)
        spacing = atoi(argv[1]);

    printf("Testing with spacing= %d\n", spacing);
    reducer_opxor_test(spacing);
    return 0;
}
