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

/* Decode a message using oneof fields */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pb_decode.h>
#include "oneof.pb.h"
#include "test_helpers.h"
#include "unittests.h"

/* Test the 'AnonymousOneOfMessage' */
int test_oneof_1(pb_istream_t *stream, int option)
{
    AnonymousOneOfMessage msg;
    int status = 0;

    /* To better catch initialization errors */
    memset(&msg, 0xAA, sizeof(msg));

    if (!pb_decode(stream, AnonymousOneOfMessage_fields, &msg))
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(stream));
        return 1;
    }

    /* Check that the basic fields work normally */
    TEST(msg.prefix == 123);
    TEST(msg.suffix == 321);

    /* Check that we got the right oneof according to command line */
    if (option == 1)
    {
        TEST(msg.which_values == AnonymousOneOfMessage_first_tag);
        TEST(msg.first == 999);
    }
    else if (option == 2)
    {
        TEST(msg.which_values == AnonymousOneOfMessage_second_tag);
        TEST(strcmp(msg.second, "abcd") == 0);
    }
    else if (option == 3)
    {
        TEST(msg.which_values == AnonymousOneOfMessage_third_tag);
        TEST(msg.third.array[0] == 1);
        TEST(msg.third.array[1] == 2);
        TEST(msg.third.array[2] == 3);
        TEST(msg.third.array[3] == 4);
        TEST(msg.third.array[4] == 5);
    }

    return status;
}

int main(int argc, char **argv)
{
    uint8_t buffer[AnonymousOneOfMessage_size];
    size_t count;
    int option;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: decode_oneof [number]\n");
        return 1;
    }
    option = atoi(argv[1]);

    SET_BINARY_MODE(stdin);
    count = fread(buffer, 1, sizeof(buffer), stdin);

    if (!feof(stdin))
    {
        printf("Message does not fit in buffer\n");
        return 1;
    }

    {
        int status = 0;
        pb_istream_t stream;

        stream = pb_istream_from_buffer(buffer, count);
        status = test_oneof_1(&stream, option);

        if (status != 0)
            return status;
    }

    return 0;
}
