#ifndef SRC_EA_SERIALIZATION_H_
#define SRC_EA_SERIALIZATION_H_
#endif

#include "cfe.h"
#include "ea_msg.h"

#include "../tools/nanopb/pb_encode.h"
#include "../tools/nanopb/pb_decode.h"
#include "ea_start.pb.h"

/* Serialization Functions */
uint32 EA_StartApp_Enc(const EA_StartCmd_t *inObject, char *inOutBuffer, uint32 inSize);
uint32 EA_StartApp_Dec(const char *inBuffer, uint32 inSize, EA_StartCmd_t *inOutObject);
