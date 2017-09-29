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

/* Checks that missing required fields are detected properly */

#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "missing_fields.pb.h"

int main()
{
    uint8_t buffer[512];
    size_t size;
    
    /* Create a message with one missing field */
    {
        MissingField msg = {0};
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
        if (!pb_encode(&stream, MissingField_fields, &msg))
        {
            printf("Encode failed.\n");
            return 1;
        }

        size = stream.bytes_written;
    }

    /* Test that it decodes properly if we don't require that field */
    {
        MissingField msg = {0};
        pb_istream_t stream = pb_istream_from_buffer(buffer, size);
        
        if (!pb_decode(&stream, MissingField_fields, &msg))
        {
            printf("Decode failed: %s\n", PB_GET_ERROR(&stream));
            return 2;
        }
    }
    
    /* Test that it does *not* decode properly if we require the field */
    {
        AllFields msg = {0};
        pb_istream_t stream = pb_istream_from_buffer(buffer, size);
        
        if (pb_decode(&stream, AllFields_fields, &msg))
        {
            printf("Decode didn't detect missing field.\n");
            return 3;
        }
    }
    
    return 0; /* All ok */
}

