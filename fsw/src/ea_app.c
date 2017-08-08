
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "ea_app.h"
#include "ea_msg.h"
#include "ea_version.h"

#include <unistd.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
EA_AppData_t  EA_AppData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 EA_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    int32  ind = 0;

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset((void*)EA_AppData.EventTbl, 0x00, sizeof(EA_AppData.EventTbl));

    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    EA_AppData.EventTbl[  ind].EventID = EA_RESERVED_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_INF_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_CONFIG_TABLE_ERR_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_CDS_ERR_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_PIPE_ERR_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_MSGID_ERR_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EA_AppData.EventTbl[  ind].EventID = EA_MSGLEN_ERR_EID;
    EA_AppData.EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(EA_AppData.EventTbl,
                               EA_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("EA - Failed to register with EVS (0x%08X)\n", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 EA_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&EA_AppData.SchPipeId,
                                 EA_SCH_PIPE_DEPTH,
                                 EA_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(EA_WAKEUP_MID, EA_AppData.SchPipeId, CFE_SB_Default_Qos, EA_SCH_PIPE_WAKEUP_RESERVED);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "Sch Pipe failed to subscribe to EA_WAKEUP_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto EA_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(EA_SEND_HK_MID, EA_AppData.SchPipeId, CFE_SB_Default_Qos, EA_SCH_PIPE_SEND_HK_RESERVED);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to EA_SEND_HK_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto EA_InitPipe_Exit_Tag;
        }

    }
    else
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create SCH pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&EA_AppData.CmdPipeId,
                                 EA_CMD_PIPE_DEPTH,
                                 EA_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(EA_CMD_MID, EA_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to EA_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto EA_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CMD pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitPipe_Exit_Tag;
    }

    /* Init data pipe and subscribe to messages on the data pipe */
    iStatus = CFE_SB_CreatePipe(&EA_AppData.DataPipeId,
                                 EA_DATA_PIPE_DEPTH,
                                 EA_DATA_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, EA_AppData.DataPipeId);
        */
    }
    else
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create Data pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitPipe_Exit_Tag;
    }

EA_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 EA_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&EA_AppData.InData, 0x00, sizeof(EA_AppData.InData));

    /* Init output data */
    memset((void*)&EA_AppData.OutData, 0x00, sizeof(EA_AppData.OutData));
    CFE_SB_InitMsg(&EA_AppData.OutData,
                   EA_OUT_DATA_MID, sizeof(EA_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&EA_AppData.HkTlm, 0x00, sizeof(EA_AppData.HkTlm));
    CFE_SB_InitMsg(&EA_AppData.HkTlm,
                   EA_HK_TLM_MID, sizeof(EA_AppData.HkTlm), TRUE);

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* EA initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 EA_InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = EA_InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("EA - Failed to init events (0x%08X)\n", (unsigned int)iStatus);
        goto EA_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = EA_InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init pipes (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitApp_Exit_Tag;
    }

    iStatus = EA_InitData();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init data (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitApp_Exit_Tag;
    }

    iStatus = EA_InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init config tables (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitApp_Exit_Tag;
    }

    iStatus = EA_InitCdsTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init CDS table (0x%08X)",
                                 (unsigned int)iStatus);
        goto EA_InitApp_Exit_Tag;
    }

EA_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(EA_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
                                 EA_MAJOR_VERSION,
                                 EA_MINOR_VERSION,
                                 EA_REVISION,
                                 EA_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_EVS_SendEvent(EA_INIT_ERR_EID, CFE_EVS_ERROR, "Application failed to initialize");
        }
        else
        {
            (void) CFE_ES_WriteToSysLog("EA - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 EA_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;
    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(EA_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, EA_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(EA_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case EA_WAKEUP_MID:
                EA_ProcessNewData();
                EA_ProcessNewCmds();
                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                 * automatically publish new output. */
                EA_SendOutData();
                break;

            case EA_SEND_HK_MID:
                EA_ReportHousekeeping();
                break;

            default:
                (void) CFE_EVS_SendEvent(EA_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid SCH msgId (0x%04X)", (unsigned short)MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else
    {
        /* TODO: This is an example of exiting on an error (either CFE_SB_BAD_ARGUMENT, or
         * CFE_SB_PIPE_RD_ERROR).
         */
        (void) CFE_EVS_SendEvent(EA_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "SB pipe read error (0x%08X), app will exit", (unsigned int)iStatus);
        EA_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Data                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   DataMsgPtr=NULL;
    CFE_SB_MsgId_t  DataMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&DataMsgPtr, EA_AppData.DataPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            DataMsgId = CFE_SB_GetMsgId(DataMsgPtr);
            switch (DataMsgId)
            {
                /* TODO:  Add code to process all subscribed data here
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         EA_ProcessNavData(DataMsgPtr);
                **         break;
                */

                default:
                    (void) CFE_EVS_SendEvent(EA_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid data msgId (0x%04X)", (unsigned short)DataMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(EA_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "Data pipe read error (0x%08X)", (unsigned int)iStatus);
            EA_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;
    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, EA_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case EA_CMD_MID:
                    EA_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         EA_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    EA_AppData.HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(EA_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(EA_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08X)", (unsigned int)iStatus);
            EA_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process EA Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;
    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case EA_NOOP_CC:
                EA_AppData.HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(EA_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd NOOP cmd (%u), Version %d.%d.%d.%d",
                                  (unsigned int)uiCmdCode,
                                  EA_MAJOR_VERSION,
                                  EA_MINOR_VERSION,
                                  EA_REVISION,
                                  EA_MISSION_REV);
                break;

            case EA_RESET_CC:
                EA_AppData.HkTlm.usCmdCnt = 0;
                EA_AppData.HkTlm.usCmdErrCnt = 0;
                memset(EA_AppData.HkTlm.ActiveApp, '\0', OS_MAX_PATH_LEN);
				EA_AppData.HkTlm.ActiveAppUtil = 0;
				EA_AppData.HkTlm.ActiveAppPID = 0;
				memset(EA_AppData.HkTlm.LastAppRun, '\0', OS_MAX_PATH_LEN);
				EA_AppData.HkTlm.LastAppStatus = 0;
				//EA_AppData.ChildTaskInUse = FALSE;

                (void) CFE_EVS_SendEvent(EA_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd RESET cmd (%u)", (unsigned int)uiCmdCode);
                break;

            case EA_START_APP_CC:
				(void) CFE_EVS_SendEvent(EA_CMD_INF_EID, CFE_EVS_INFORMATION,
								  "Recvd Start App cmd (%u)", (unsigned int)uiCmdCode);
				EA_StartApp(MsgPtr);
				break;

            case EA_TERM_APP_CC:
				(void) CFE_EVS_SendEvent(EA_CMD_INF_EID, CFE_EVS_INFORMATION,
								  "Recvd Terminate App cmd (%u)", (unsigned int)uiCmdCode);
            	EA_TermApp(MsgPtr);
				break;


            /* TODO:  Add code to process the rest of the EA commands here */

            default:
                EA_AppData.HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(EA_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* EA Start App                                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_StartApp(CFE_SB_Msg_t* MsgPtr)
{
	/* command verification variables */
	uint16              ExpectedLength = sizeof(EA_StartCmd_t);
	uint32              ChildTaskID;
	int32               Status;
	EA_StartCmd_t  *CmdPtr = 0;
	char DEF_INTERPRETER[OS_MAX_PATH_LEN] = "/usr/bin/python";
	char DEF_SCRIPT[OS_MAX_PATH_LEN] = "/home/vagrant/prototype/ea_proto/test_py.py";

	/* Verify command packet length... */
	if (EA_VerifyCmdLength (MsgPtr,ExpectedLength))
	{
		if (EA_AppData.ChildTaskInUse == FALSE)
		{
			CmdPtr = ((EA_StartCmd_t *) MsgPtr);

			/*
			** Check if the interpreter string is a nul string
			*/
			if(strlen(CmdPtr->interpreter) == 0)
			{
				strcpy(CmdPtr->interpreter, DEF_INTERPRETER);
			}

			/*
			** Check if the filename string is a nul string
			*/
			if(strlen(CmdPtr->script) == 0)
			{
				strcpy(CmdPtr->script, DEF_SCRIPT);
			}

			/*
			** NUL terminate the very end of the filename string as a
			** safety measure
			*/
			CmdPtr->interpreter[OS_MAX_PATH_LEN - 1] = '\0';
			CmdPtr->script[OS_MAX_PATH_LEN - 1] = '\0';

			/*
			** Check if specified interpreter exists
			*/
			if(access(CmdPtr->interpreter, F_OK ) != -1)
			{
				/*
				** Check if specified script exists
				*/
				if(access(CmdPtr->script, F_OK ) != -1)
				{
					/*
					** Update ChildData with validated data
					*/
					strcpy(EA_AppData.ChildData.AppInterpreter, CmdPtr->interpreter);
					strcpy(EA_AppData.ChildData.AppScript, CmdPtr->script);

					/* There is no child task running right now, we can use it*/
					EA_AppData.ChildTaskInUse = TRUE;

					Status = CFE_ES_CreateChildTask(&ChildTaskID,
													EA_START_APP_TASK_NAME,
													EA_StartAppCustom,
													NULL,
													CFE_ES_DEFAULT_STACK_SIZE,
													EA_CHILD_TASK_PRIORITY,
													0);
					if (Status == CFE_SUCCESS)
					{
						CFE_EVS_SendEvent (EA_CHILD_TASK_START, CFE_EVS_DEBUG, "Created child task for app start.");

						EA_AppData.ChildTaskID = ChildTaskID;
					}
					else/* child task creation failed */
					{
						CFE_EVS_SendEvent (EA_CHILD_TASK_START_ERR_EID,
										   CFE_EVS_ERROR,
										   "Create child tasked failed. Unable to start external application.",
										   Status);

						EA_AppData.HkTlm.usCmdErrCnt++;
						EA_AppData.ChildTaskInUse   = FALSE;
						memset(EA_AppData.ChildData.AppInterpreter, '\0', OS_MAX_PATH_LEN);
						memset(EA_AppData.ChildData.AppScript, '\0', OS_MAX_PATH_LEN);
					}

				}
				else
				{
					EA_AppData.HkTlm.usCmdErrCnt++;
					CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
						"Specified script does not exist");
				}
			}
			else
			{
				EA_AppData.HkTlm.usCmdErrCnt++;
				CFE_EVS_SendEvent(EA_CMD_ERR_EID, CFE_EVS_ERROR,
					"Specified interpreter does not exist");
			}
		}
		else
		{
			/*send event that we can't start another task right now */
			CFE_EVS_SendEvent (EA_CHILD_TASK_START_ERR_EID,
							   CFE_EVS_ERROR,
							   "Create child tasked failed. A child task is in use");

			EA_AppData.HkTlm.usCmdErrCnt++;
		}
	}
	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* EA Terminate App                                                */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_TermApp(CFE_SB_Msg_t* MsgPtr)
{
	EA_TermAppCustom(MsgPtr);
	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* EA Performance Monitor                                          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_Perfmon()
{
	if(EA_AppData.HkTlm.ActiveAppPID != 0)
	{
		uint8 util = 0;
		uint8 cpu_ndx = EA_CalibrateTop(EA_AppData.HkTlm.ActiveAppPID);
		//OS_printf("CPU index: %i\n", cpu_ndx);

		util = EA_GetPidUtil(EA_AppData.HkTlm.ActiveAppPID, cpu_ndx);
	}
	else
	{
		//OS_printf("Cannot perform perfmon with no running task.\n");
	}
	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send EA Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&EA_AppData.HkTlm);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&EA_AppData.HkTlm);
    if (iStatus != CFE_SUCCESS)
    {
        /* TODO: Decide what to do if the send message fails. */
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&EA_AppData.OutData);
    int32 iStatus = CFE_SB_SendMsg((CFE_SB_Msg_t*)&EA_AppData.OutData);
    if (iStatus != CFE_SUCCESS)
    {
        /* TODO: Decide what to do if the send message fails. */
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

boolean EA_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult  = TRUE;
    uint16  usMsgLen = 0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(EA_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            EA_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* EA application entry point and main process loop               */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void EA_AppMain()
{
    /* Register the application with Executive Services */
    EA_AppData.uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("EA - Failed to register the app (0x%08X)\n", (unsigned int)iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(EA_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = EA_InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(EA_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(EA_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(EA_MAIN_TASK_PERF_ID);
    }
    else
    {
        EA_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&EA_AppData.uiRunStatus) == TRUE)
    {
//    	OS_printf("iStatus: %i\n", iStatus);
        int32 iStatus = EA_RcvMsg(EA_SCH_PIPE_PEND_TIME);
        if (iStatus != CFE_SUCCESS)
        {
        	OS_printf("iStatus does not = CFE_SUCCESS\n");
        	/* TODO: Decide what to do for other return values in EA_RcvMsg(). */
        }
        EA_Perfmon();
        /* TODO: This is only a suggestion for when to update and save CDS table.
        ** Depends on the nature of the application, the frequency of update
        ** and save can be more or less independently.
        */
        //EA_UpdateCdsTbl();
        //EA_SaveCdsTbl();
        iStatus = EA_AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            EA_AppData.uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(EA_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(EA_AppData.uiRunStatus);
}

/************************/
/*  End of File Comment */
/************************/
