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
* 3. Neither the name Windhover Labs nor the names of its 
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

/* Simulate IO errors after each byte in a stream.
 * Verifies proper error propagation.
 */

#include <stdio.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include "alltypes.pb.h"
#include "test_helpers.h"

typedef struct
{
    uint8_t *buffer;
    size_t fail_after;
} faulty_stream_t;

bool read_callback(pb_istream_t *stream, uint8_t *buf, size_t count)
{
    faulty_stream_t *state = stream->state;
    
    while (count--)
    {
        if (state->fail_after == 0)
            PB_RETURN_ERROR(stream, "simulated");
        state->fail_after--;
        *buf++ = *state->buffer++;
    }
    
    return true;
}
bool write_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count)
{
    faulty_stream_t *state = stream->state;
    
    while (count--)
    {
        if (state->fail_after == 0)
            PB_RETURN_ERROR(stream, "simulated");
        state->fail_after--;
        *state->buffer++ = *buf++;
    }
    
    return true;
}

int main()
{
    uint8_t buffer[2048];
    size_t msglen;
    AllTypes msg = AllTypes_init_zero;
    
    /* Get some base data to run the tests with */
    SET_BINARY_MODE(stdin);
    msglen = fread(buffer, 1, sizeof(buffer), stdin);
    
    /* Test IO errors on decoding */
    {
        bool status;
        pb_istream_t stream = {&read_callback, NULL, SIZE_MAX};
        faulty_stream_t fs;
        size_t i;
        
        for (i = 0; i < msglen; i++)
        {
            stream.bytes_left = msglen;
            stream.state = &fs;
            fs.buffer = buffer;
            fs.fail_after = i;

            status = pb_decode(&stream, AllTypes_fields, &msg);
            if (status != false)
            {
                fprintf(stderr, "Unexpected success in decode\n");
                return 2;
            }
            else if (strcmp(stream.errmsg, "simulated") != 0)
            {
                fprintf(stderr, "Wrong error in decode: %s\n", stream.errmsg);
                return 3;
            }
        }
        
        stream.bytes_left = msglen;
        stream.state = &fs;
        fs.buffer = buffer;
        fs.fail_after = msglen;
        status = pb_decode(&stream, AllTypes_fields, &msg);
        
        if (!status)
        {
            fprintf(stderr, "Decoding failed: %s\n", stream.errmsg);
            return 4;
        }
    }
    
    /* Test IO errors on encoding */
    {
        bool status;
        pb_ostream_t stream = {&write_callback, NULL, SIZE_MAX, 0};
        faulty_stream_t fs;
        size_t i;
        
        for (i = 0; i < msglen; i++)
        {
            stream.max_size = msglen;
            stream.bytes_written = 0;
            stream.state = &fs;
            fs.buffer = buffer;
            fs.fail_after = i;

            status = pb_encode(&stream, AllTypes_fields, &msg);
            if (status != false)
            {
                fprintf(stderr, "Unexpected success in encode\n");
                return 5;
            }
            else if (strcmp(stream.errmsg, "simulated") != 0)
            {
                fprintf(stderr, "Wrong error in encode: %s\n", stream.errmsg);
                return 6;
            }
        }
        
        stream.max_size = msglen;
        stream.bytes_written = 0;
        stream.state = &fs;
        fs.buffer = buffer;
        fs.fail_after = msglen;
        status = pb_encode(&stream, AllTypes_fields, &msg);
        
        if (!status)
        {
            fprintf(stderr, "Encoding failed: %s\n", stream.errmsg);
            return 7;
        }
    }

    return 0;   
}

