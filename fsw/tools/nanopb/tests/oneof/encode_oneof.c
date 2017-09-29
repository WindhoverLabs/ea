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

/* Encode a message using oneof fields */

#include <stdio.h>
#include <stdlib.h>
#include <pb_encode.h>
#include "oneof.pb.h"
#include "test_helpers.h"

int main(int argc, char **argv)
{
    uint8_t buffer[OneOfMessage_size];
    OneOfMessage msg = OneOfMessage_init_zero;
    pb_ostream_t stream;
    int option;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: encode_oneof [number]\n");
        return 1;
    }
    option = atoi(argv[1]);

    /* Prefix and suffix are used to test that the union does not disturb
     * other fields in the same message. */
    msg.prefix = 123;

    /* We encode one of the 'values' fields based on command line argument */
    if (option == 1)
    {
        msg.which_values = OneOfMessage_first_tag;
        msg.values.first = 999;
    }
    else if (option == 2)
    {
        msg.which_values = OneOfMessage_second_tag;
        strcpy(msg.values.second, "abcd");
    }
    else if (option == 3)
    {
        msg.which_values = OneOfMessage_third_tag;
        msg.values.third.array_count = 5;
        msg.values.third.array[0] = 1;
        msg.values.third.array[1] = 2;
        msg.values.third.array[2] = 3;
        msg.values.third.array[3] = 4;
        msg.values.third.array[4] = 5;
    }

    msg.suffix = 321;

    stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    if (pb_encode(&stream, OneOfMessage_fields, &msg))
    {
        SET_BINARY_MODE(stdout);
        fwrite(buffer, 1, stream.bytes_written, stdout);
        return 0;
    }
    else
    {
        fprintf(stderr, "Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }
}
