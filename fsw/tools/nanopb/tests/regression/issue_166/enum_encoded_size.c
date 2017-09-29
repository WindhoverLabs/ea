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

#include <stdio.h>
#include <string.h>
#include <pb_encode.h>
#include "unittests.h"
#include "enums.pb.h"

int main()
{
    int status = 0;
    
    uint8_t buf[256];
    SignedMsg msg1;
    UnsignedMsg msg2;
    pb_ostream_t s;
    
    {
        COMMENT("Test negative value of signed enum");
        /* Negative value should take up the maximum size */
        msg1.value = SignedEnum_SE_MIN;
        s = pb_ostream_from_buffer(buf, sizeof(buf));
        TEST(pb_encode(&s, SignedMsg_fields, &msg1));
        TEST(s.bytes_written == SignedMsg_size);
        
        COMMENT("Test positive value of signed enum");
        /* Positive value should be smaller */
        msg1.value = SignedEnum_SE_MAX;
        s = pb_ostream_from_buffer(buf, sizeof(buf));
        TEST(pb_encode(&s, SignedMsg_fields, &msg1));
        TEST(s.bytes_written < SignedMsg_size);
    }
    
    {
        COMMENT("Test positive value of unsigned enum");
        /* This should take up the maximum size */
        msg2.value = UnsignedEnum_UE_MAX;
        s = pb_ostream_from_buffer(buf, sizeof(buf));
        TEST(pb_encode(&s, UnsignedMsg_fields, &msg2));
        TEST(s.bytes_written == UnsignedMsg_size);
    }
    
    return status;
}

