#ifndef EA_CUSTOM_H
#define EA_CUSTOM_H

#include "cfe.h"

int32 EA_StartAppCustom(CFE_SB_Msg_t* MsgPtr);
int32 EA_TermAppCustom(CFE_SB_Msg_t* MsgPtr);
int32 EA_PerfmonCustom(CFE_SB_Msg_t* MsgPtr);
uint8 EA_GetPidUtil(int pid);

#endif
