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

/* This program takes a command line argument and encodes a message in
 * one of MsgType1, MsgType2 or MsgType3.
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <pb_encode.h>
#include "unionproto.pb.h"

/* This function is the core of the union encoding process. It handles
 * the top-level pb_field_t array manually, in order to encode a correct
 * field tag before the message. The pointer to MsgType_fields array is
 * used as an unique identifier for the message type.
 */
bool encode_unionmessage(pb_ostream_t *stream, const pb_field_t messagetype[], const void *message)
{
    const pb_field_t *field;
    for (field = UnionMessage_fields; field->tag != 0; field++)
    {
        if (field->ptr == messagetype)
        {
            /* This is our field, encode the message using it. */
            if (!pb_encode_tag_for_field(stream, field))
                return false;
            
            return pb_encode_submessage(stream, messagetype, message);
        }
    }
    
    /* Didn't find the field for messagetype */
    return false;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s (1|2|3)\n", argv[0]);
        return 1;
    }
    
    uint8_t buffer[512];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    bool status = false;
    int msgtype = atoi(argv[1]);
    if (msgtype == 1)
    {
        /* Send message of type 1 */
        MsgType1 msg = {42};
        status = encode_unionmessage(&stream, MsgType1_fields, &msg);
    }
    else if (msgtype == 2)
    {
        /* Send message of type 2 */
        MsgType2 msg = {true};
        status = encode_unionmessage(&stream, MsgType2_fields, &msg);
    }
    else if (msgtype == 3)
    {
        /* Send message of type 3 */
        MsgType3 msg = {3, 1415};
        status = encode_unionmessage(&stream, MsgType3_fields, &msg);
    }
    else
    {
        fprintf(stderr, "Unknown message type: %d\n", msgtype);
        return 2;
    }
    
    if (!status)
    {
        fprintf(stderr, "Encoding failed!\n");
        return 3;
    }
    else
    {
        fwrite(buffer, 1, stream.bytes_written, stdout);
        return 0; /* Success */
    }
}


