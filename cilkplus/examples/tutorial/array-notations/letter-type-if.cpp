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
 * letter-type-if.cpp
 *
 * Demonstrate testing each element of an array using  both for loop and Array
 * Notation
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char a[] = "Hello world";

    printf ("Check letter types using for loop:\n");
    for (int i = 0; i < sizeof(a); i++)
    {
        if (('a' == a[i]) ||
            ('e' == a[i]) ||
            ('i' == a[i]) ||
            ('o' == a[i]) ||
            ('u' == a[i]))
            printf("%c: Vowel %d\n", a[i], a[i]);
        else
        {
            if ('\0' == a[i])
                printf("   NUL\n");
            else
            {
                if (' ' == a[i])
                    printf("   Space\n");
                else
                    printf("%c: Consonant: %d\n", a[i], a[i]);
            }
        }
    }

    printf ("\nCheck letter types using Array Notation:\n");
    if (('a' == a[:]) ||
        ('e' == a[:]) ||
        ('i' == a[:]) ||
        ('o' == a[:]) ||
        ('u' == a[:]))
        printf("%c: Vowel: %d\n", a[:], a[:]);
    else
    {
        if ('\0' == a[:])
            printf("   NUL\n");
        {
            if (' ' == a[:])
                printf("   Space\n");
            else
                printf("%c: Consonant: %d\n", a[:], a[:]);
        }
    }

    return 0;
}
