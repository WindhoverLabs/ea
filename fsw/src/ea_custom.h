#ifndef EA_CUSTOM_H
#define EA_CUSTOM_H

#include "cfe.h"
#include <unistd.h>

void EA_StartAppCustom();
void EA_TermAppCustom(CFE_SB_Msg_t* MsgPtr);
int32 EA_PerfmonCustom(CFE_SB_Msg_t* MsgPtr);
uint8 EA_CalibrateTop(int32 pid);
uint8 EA_GetPidUtil(int32 pid, uint8 util_ndx);

#endif
