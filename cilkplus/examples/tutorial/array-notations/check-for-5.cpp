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
 * check-for-5.cpp
 *
 * Demonstrate using an if statement with elements of an array using
 * both a for loop and Array Notation
 */

#include <stdio.h>
#include <string.h>

const int array_size=10;

int main(int argc, char **argv)
{
    int a[array_size];
    const char *loop_results[array_size];
    const char *an_results[array_size];

    // Initialize array using for loop
    for (int i = 0; i < array_size; i++)
        a[i] = i;

    // Check for 5 using a for loop
    printf ("Check for array element containing 5 using for loop:\n");
    for (int i = 0; i < array_size; i++)
    {
        if (5 == a[i])
            loop_results[i] = "Matched";
        else
            loop_results[i] = "Not Matched";
    }

    // Check for 5 using Array Notation
    printf ("\nCheck for array element containing 5 using Array Notation:\n");
    if (5 == a[:])
        an_results[:] = "Matched";
    else
        an_results[:] = "Not Matched";

    // Verify the results
    bool success = true;
    for (int i = 0; i < array_size; i++)
    {
        if (strcmp(loop_results[i], an_results[i]))
            success = false;
    }

    if (success)
        printf("Results match\n");
    else
        printf("Results differ!\n");

    return 0;
}
