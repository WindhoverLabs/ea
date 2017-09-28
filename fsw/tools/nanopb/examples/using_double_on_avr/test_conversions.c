/****************************************************************************
 *
 *   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "double_conversion.h"
#include <math.h>
#include <stdio.h>

static const double testvalues[] = {
           0.0,        -0.0,         0.1,         -0.1,
          M_PI,       -M_PI,  123456.789,  -123456.789,
      INFINITY,   -INFINITY,         NAN, INFINITY - INFINITY,
          1e38,       -1e38,        1e39,        -1e39,
         1e-38,      -1e-38,       1e-39,       -1e-39,
   3.14159e-37,-3.14159e-37, 3.14159e-43, -3.14159e-43,
         1e-60,      -1e-60,       1e-45,       -1e-45,
    0.99999999999999, -0.99999999999999, 127.999999999999, -127.999999999999
};

#define TESTVALUES_COUNT (sizeof(testvalues)/sizeof(testvalues[0]))

int main()
{
    int status = 0;
    int i;
    for (i = 0; i < TESTVALUES_COUNT; i++)
    {
        double orig = testvalues[i];
        float expected_float = (float)orig;
        double expected_double = (double)expected_float;
        
        float got_float = double_to_float(*(uint64_t*)&orig);
        uint64_t got_double = float_to_double(got_float);
        
        uint32_t e1 = *(uint32_t*)&expected_float;
        uint32_t g1 = *(uint32_t*)&got_float;
        uint64_t e2 = *(uint64_t*)&expected_double;
        uint64_t g2 = got_double;
        
        if (g1 != e1)
        {
            printf("%3d double_to_float fail: %08x != %08x\n", i, g1, e1);
            status = 1;
        }
        
        if (g2 != e2)
        {
            printf("%3d float_to_double fail: %016llx != %016llx\n", i,
                (unsigned long long)g2,
                (unsigned long long)e2);
            status = 1;
        }
    }

    return status;
}

    
    

