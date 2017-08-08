    
#ifndef EA_MSG_H
#define EA_MSG_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** EA Command Codes
*************************************************************************/

/** \eacmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the EA task is alive
**
**  \eacmdmnemonic \EA_NOOP
**
**  \par Command Structure
**       #EA_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \EA_CMDACPTCNT - command counter will increment
**       - The #EA_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \EA_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #EA_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #EA_RESET_CC
*/
#define EA_NOOP_CC                 (0)

/** \eacmd Reset Counters
**  
**  \par Description
**       Resets the ea housekeeping counters
**
**  \eacmdmnemonic \EA_TLMRST
**
**  \par Command Structure
**       #EA_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \EA_CMDACTPCNT       - command counter will be cleared
**       - \b \c \EA_CMDRJCTCNT       - command error counter will be cleared
**       - The #EA_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \EA_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #EA_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #EA_NOOP_CC
*/
#define EA_RESET_CC                (1)

/** \eacmd Start Application
**
**  \par Description
**       Starts external application
**
**  \eacmdmnemonic \EA_
**
**  \par Command Structure
**       #EA_StartCmd_t
**
**  \par Command Verification TODO
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \EA_CMDACTPCNT       - command counter will be cleared
**       - \b \c \EA_CMDRJCTCNT       - command error counter will be cleared
**       - The #EA_CMD_INF_EID debug event message will be
**         generated when the command is executed
**
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
**
**  \par Evidence of failure may be found in the following telemetry:
**       - \b \c \EA_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #EA_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #EA_NOOP_CC
*/
#define EA_START_APP_CC                (2)

/** \eacmd Reset Counters TODO
**
**  \par Description
**       Resets the ea housekeeping counters
**
**  \eacmdmnemonic \EA_TLMRST
**
**  \par Command Structure
**       #EA_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \EA_CMDACTPCNT       - command counter will be cleared
**       - \b \c \EA_CMDRJCTCNT       - command error counter will be cleared
**       - The #EA_CMD_INF_EID debug event message will be
**         generated when the command is executed
**
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
**
**  \par Evidence of failure may be found in the following telemetry:
**       - \b \c \EA_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #EA_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #EA_NOOP_CC
*/
#define EA_TERM_APP_CC                (3)

/** \eacmd Reset Counters TODO
**
**  \par Description
**       Resets the ea housekeeping counters
**
**  \eacmdmnemonic \EA_TLMRST
**
**  \par Command Structure
**       #EA_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \EA_CMDACTPCNT       - command counter will be cleared
**       - \b \c \EA_CMDRJCTCNT       - command error counter will be cleared
**       - The #EA_CMD_INF_EID debug event message will be
**         generated when the command is executed
**
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
**
**  \par Evidence of failure may be found in the following telemetry:
**       - \b \c \EA_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #EA_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #EA_NOOP_CC
*/
#define EA_PERFMON_CC                (4)



/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #EA_NOOP_CC, #EA_RESET_CC
**  Also see #EA_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} EA_NoArgCmd_t;

/** TODO
**  \brief No Arguments Command
**  For command details see #EA_NOOP_CC, #EA_RESET_CC
**  Also see #EA_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
    char   interpreter[OS_MAX_PATH_LEN];
    char   script[OS_MAX_PATH_LEN];

} EA_StartCmd_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific incoming data
*/
typedef struct
{
    uint8   TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices.
    **        Option: for data that is already defined by another app, include
    **        that app's message header above.
    */

} EA_InData_t;

/** 
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} EA_OutData_t;

/** 
**  \brief EA application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \eatlmmnemonic \EA_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \eatlmmnemonic \EA_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 

    /** \eatlmmnemonic \EA_
            \brief Name of current running application */
    char			   ActiveApp[OS_MAX_PATH_LEN];

    /** \eatlmmnemonic \EA_
		\brief CPU utilization of current running application */
    float			   ActiveAppUtil;

    /** \eatlmmnemonic \EA_
    		\brief Padding to correctly allign */
    //uint8				padding;

    /** \eatlmmnemonic \EA_
		\brief PID of current running application */
    int32			   ActiveAppPID;

    /** \eatlmmnemonic \EA_
		\brief Name of last run application */
    char			   LastAppRun[OS_MAX_PATH_LEN];

    /** \eatlmmnemonic \EA_
		\brief Last run application return code */
    int32			   LastAppStatus;

} EA_HkTlm_t;

/**
**  \brief TODO Elaborate this struct
**  Boilerplate example of application-specific outgoing data
*/
typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    char	AppInterpreter[OS_MAX_PATH_LEN];
    char	AppScript[OS_MAX_PATH_LEN];

} EA_ChildData_t;


#ifdef __cplusplus
}
#endif

#endif /* EA_MSG_H */

/************************/
/*  End of File Comment */
/************************/
