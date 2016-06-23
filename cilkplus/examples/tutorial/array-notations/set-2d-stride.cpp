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
 * set-2d-stride.cpp
 *
 * Demonstrate setting all elements of a 2D array to a value using both for loop
 * and Array Notation
 */

#include <stdio.h>
#include <string.h>

const int array_size=10;

int main(int argc, char **argv)
{
    int i, j;
    int a[array_size][array_size];
    int b[array_size][array_size];

    // Initialize array using for loops
    for (i = 0; i < array_size; i++)
        for (j = 0; j < array_size; j++)
            a[i][j] = 5;

    // Set even rows using for loop
    for (i = 0; i < array_size; i += 2)
    {
        for (j = 0; j < array_size; j++)
            a[i][j] = 12;
    }

    // Initialize the array using Array Notation.  Since the array is
    // statically allocated, we can use default values for the start index (0)
    // and number of elements (all of them).
    b[:][:] = 5;

    // Set elements of even rows to 12
    b[0:5:2][:] = 12;

    // Verify the results - The arrays should be identical
    if (0 == memcmp(a, b, sizeof(a)))
        printf("Success\n");
    else
        printf("Failed\n");

    return 0;
}
