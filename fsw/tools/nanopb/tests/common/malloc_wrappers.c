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
* 3. Neither the name Windhover Labs, L.L.C. nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
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
*****************************************************************************/

#include "malloc_wrappers.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>

static size_t alloc_count = 0;

/* Allocate memory and place check values before and after. */
void* malloc_with_check(size_t size)
{
    size_t size32 = (size + 3) / 4 + 3;
    uint32_t *buf = malloc(size32 * sizeof(uint32_t));
    buf[0] = size32;
    buf[1] = 0xDEADBEEF;
    buf[size32 - 1] = 0xBADBAD;
    return buf + 2;
}

/* Free memory allocated with malloc_with_check() and do the checks. */
void free_with_check(void *mem)
{
    uint32_t *buf = (uint32_t*)mem - 2;
    assert(buf[1] == 0xDEADBEEF);
    assert(buf[buf[0] - 1] == 0xBADBAD);
    free(buf);
}

/* Track memory usage */
void* counting_realloc(void *ptr, size_t size)
{
    /* Don't allocate crazy amounts of RAM when fuzzing */
    if (size > 1000000)
        return NULL;

    if (!ptr && size)
        alloc_count++;
    
    return realloc(ptr, size);
}

void counting_free(void *ptr)
{
    if (ptr)
    {
        assert(alloc_count > 0);
        alloc_count--;
        free(ptr);
    }
}

size_t get_alloc_count()
{
    return alloc_count;
}
