#include "ea_serialization.h"

uint32 EA_StartApp_Enc(const EA_StartCmd_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	ea_start_pb pbMsg;
	
	//pbMsg.interpreter = inObject->interpreter;
	//pbMsg.script = inObject->script;
    //strcpy(pbMsg.interpreter, inObject->interpreter);
    //strcpy(pbMsg.script, inObject->script);


	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, ea_start_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 EA_StartApp_Dec(const char *inBuffer, uint32 inSize, EA_StartCmd_t *inOutObject)
{
	bool status = false;
	ea_start_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, ea_start_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
	
	//inOutObject->interpreter = pbMsg.interpreter;
	//inOutObject->script = pbMsg.script;


	return sizeof(EA_StartCmd_t);
}
