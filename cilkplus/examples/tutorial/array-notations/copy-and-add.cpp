/*
 * Copyright (C) 2012, Intel Corporation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * copy-and-add.cpp
 *
 * Demonstrate copying all elements of an array from another array using both
 * for loop and Array Notation
 */

#include <stdio.h>
#include <string.h>

const int array_size=10;

int main(int argc, char **argv)
{
    int a[array_size], b[array_size], c[array_size];

    // Initialize array a using for loop
    for (int i = 0; i < array_size; i++)
        a[i] = i;

    // Copy data adding 5 using for loop
    for (int i = 0; i < array_size; i++)
        b[i] = a[i] + 5;

    // Copy the array using Array Notation.  Since the array is statically
    // allocated, we can use default values for the start index (0) and
    // number of elements (all of them).
    c[:] = a[:] + 5;

    // Verify the results - The arrays should be identical
    if (0 == memcmp(b, c, sizeof(b)))
        printf("Success\n");
    else
        printf("Failed\n");

    return 0;
}
