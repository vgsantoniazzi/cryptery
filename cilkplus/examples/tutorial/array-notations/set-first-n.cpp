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
 * set-first-n.cpp
 *
 * Demonstrate setting a sequence of elements of an array to a value using
 * both loops and Array Notation where the length of the sequence is not a
 * constant
 */

#include <stdio.h>
#include <string.h>

const int array_size=10;

int main(int argc, char **argv)
{
    int a[array_size];
    int b[array_size];
    int n = 3;

    // Setting a sequence of elements of an array to a value array using for
    // loop
    for (int i = 0; i < array_size; i++)
        a[i] = 5;
    for (int i = 0; i < n; i++)
        a[i] = 4;

    // Setting a sequence of elements of an array to a value array using Array
    // Notation
    b[:] = 5;   // Fill array with 5
    b[0:n] = 4; // Fill first N with 4

    // Verify the results - Arrays should be identical
    if (0 == memcmp(a, b, sizeof(a)))
        printf("Success\n");
    else
        printf("Failed\n");

    return 0;
}
