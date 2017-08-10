#include "ea_custom_stub.h"
#include "ea_platform_cfg.h"
#include "ea_app.h"
#include "ea_msg.h"

void EA_StartAppCustom()
{
	EA_AppData.HkTlm.usCmdCnt++;
	return;
}

void EA_TermAppCustom(CFE_SB_Msg_t* MsgPtr)
{
	if(EA_AppData.HkTlm.ActiveAppPID != 0)
	{
		EA_AppData.HkTlm.usCmdCnt++;
		EA_AppData.HkTlm.ActiveAppPID = 0;
		CFE_EVS_SendEvent(EA_INF_APP_TERM_EID, CFE_EVS_INFORMATION,
						"External application terminated");
	}
	else
	{
		EA_AppData.HkTlm.usCmdErrCnt++;
		CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
						"Attempted to terminate app while none executing");
	}

	return;
}

void EA_PerfmonCustom(int32 pid)
{
	if(EA_AppData.HkTlm.ActiveAppPID != 0)
	{
		if(EA_AppData.HkTlm.ActiveAppUtil > EA_APP_UTIL_THRESHOLD)
		{
			CFE_EVS_SendEvent(EA_WARN_APP_UTIL_EID, CFE_EVS_INFORMATION,
								"External application exceeded utilization threshold");
		}
		EA_AppData.HkTlm.ActiveAppUtil = 1;
	}
	return;
}

EA_ProcData_t EA_ParsePidUtil(int32 pid)
{
	EA_ProcData_t procData;
	procData.p_time = 1;
	procData.p_time = 1;
	return(procData);
}










