#include "ea_serialization.h"

uint32 EA_StartCmd_t_Enc(const EA_StartCmd_t *inObject, char *inOutBuffer, uint32 inSize)
{
	OS_printf("IN SERIALIZE\n");
	bool status = false;
	ea_start_pb pbMsg;
	
	//pbMsg.interpreter = inObject->interpreter;
	//pbMsg.script = inObject->script;
    strcpy(pbMsg.interpreter, inObject->interpreter);
    strcpy(pbMsg.script, inObject->script);
//    OS_printf("set vars\n");
//
    OS_printf("inObject script %s\n", inObject->script);
    OS_printf("inObject interpreter %s\n", inObject->interpreter);
    OS_printf("pb script %s\n", pbMsg.script);
    OS_printf("pb interpreter %s\n", pbMsg.interpreter);

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);
	//OS_printf("made stream\n");
	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, ea_start_pb_fields, &pbMsg);
	OS_printf("encoded: %s\n", inOutBuffer);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 EA_StartCmd_t_Dec(const char *inBuffer, uint32 inSize, EA_StartCmd_t *inOutObject)
{
	OS_printf("IN DESERIALIZE\n");
	bool status = false;
	ea_start_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	OS_printf("made stream\n");
	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, ea_start_pb_fields, &pbMsg);
	OS_printf("decoded\n");
	OS_printf("Status: %i\n", status);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
	
	OS_printf("pb script %s\n", pbMsg.script);
	OS_printf("pb interpreter %s\n", pbMsg.interpreter);


	//inOutObject->interpreter = pbMsg.interpreter;
	//inOutObject->script = pbMsg.script;
    strcpy(inOutObject->interpreter, pbMsg.interpreter);
    strcpy(inOutObject->script, pbMsg.script);

	OS_printf("inOutObject script %s\n", inOutObject->script);
	OS_printf("inOutObject interpreter %s\n", inOutObject->interpreter);

    OS_printf("set vars\n");
	return sizeof(EA_StartCmd_t);
}
