    
#ifndef EA_APP_H
#define EA_APP_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

#include "ea_platform_cfg.h"
#include "ea_mission_cfg.h"
#include "ea_private_ids.h"
#include "ea_private_types.h"
#include "ea_perfids.h"
#include "ea_msgids.h"
#include "ea_msg.h"
#include "ea_events.h"
#include "ea_config_utils.h"
#include "ea_cds_utils.h"
#include "ea_custom.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/
#define EA_TIMEOUT_MSEC             	(1000)
#define EA_START_APP_TASK_NAME            "EA_StartAppCustom"

/************************************************************************
** Local Structure Definitions
*************************************************************************/
/**
**  \brief EA Operational Data Structure
*/
typedef struct
{
    /** \brief CFE Event Table */
    CFE_EVS_BinFilter_t  EventTbl[EA_EVT_CNT];

    /**\brief Scheduling Pipe ID */
    CFE_SB_PipeId_t  SchPipeId;

    /** \brief Command Pipe ID */
    CFE_SB_PipeId_t  CmdPipeId;

    /** \brief Data Pipe ID */
    CFE_SB_PipeId_t  DataPipeId;

    /* Task-related */

    /** \brief Task Run Status */
    uint32  uiRunStatus;

    /* Config table-related */

    /** \brief Config Table Handle */
    CFE_TBL_Handle_t  ConfigTblHdl;

    /** \brief Config Table Pointer */
    EA_ConfigTblEntry_t*  ConfigTblPtr;

    /* Critical Data Storage (CDS) table-related */

    /** \brief CDS Table Handle */
    CFE_ES_CDSHandle_t  CdsTblHdl;

    /** \brief CDS Table data */
    EA_CdsTbl_t  CdsTbl;

    /* Inputs/Outputs */

    /** \brief Input Data from I/O or other apps */
    EA_InData_t   InData;

    /** \brief Output Data published at the end of cycle */
    EA_OutData_t  OutData;

    /**< \brief Flag for a child task in use */
    boolean  ChildAppTaskInUse;

    /**< \brief Task ID for the child task */
    uint32  ChildAppTaskID;

    /** \brief Housekeeping Telemetry for downlink */
    EA_HkTlm_t  HkTlm;

    /** \brief Info child task needs to launch external app */
    EA_ChildData_t ChildData;

    /** \brief Process info for external app */
    EA_ProcData_t ProcData;


} EA_AppData_t;

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief CFS External Applications Task (EA) application entry point
**
**  \par Description
**       CFS External Applications Task application entry point.  This function
**       performs app initialization, then waits for the cFE ES Startup
**       Sync, then executes the RPR main processing loop.
**
**  \par Assumptions, External Events, and Notes:
**       If there is an unrecoverable failure during initialization the
**       main loop is never executed and the application will exit.
**
*************************************************************************/
void  EA_AppMain(void);

/************************************************************************/
/** \brief Initialize the CFS External Applications (EA) application
**
**  \par Description
**       External Applications application initialization routine. This
**       function performs all the required startup steps to
**       initialize (or restore from CDS) EA data structures and get
**       the application registered with the cFE services so it can
**       begin to receive command messages and send events.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
**  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
**  \retstmt Return codes from #EA_InitEvent               \endcode
**  \retstmt Return codes from #EA_InitPipe                \endcode
**  \retstmt Return codes from #EA_InitData                \endcode
**  \retstmt Return codes from #EA_InitConfigTbl           \endcode
**  \retstmt Return codes from #EA_InitCdsTbl              \endcode
**  \retstmt Return codes from #OS_TaskInstallDeleteHandler \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitApp(void);

/************************************************************************/
/** \brief Initialize Event Services and Event tables
**
**  \par Description
**       This function performs the steps required to setup
**       cFE Event Services for use by the EA application.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_EVS_Register  \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitEvent(void);

/************************************************************************/
/** \brief Initialize global variables used by EA application
**
**  \par Description
**       This function performs the steps required to initialize
**       the EA application data.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_EVS_Register  \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitData(void);

/************************************************************************/
/** \brief Initialize message pipes
**
**  \par Description
**       This function performs the steps required to setup
**       initialize the cFE Software Bus message pipes and subscribe to
**       messages for the EA application.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_CreatePipe        \endcode
**  \retstmt Return codes from #CFE_SB_SubscribeEx       \endcode
**  \retstmt Return codes from #CFE_SB_Subscribe         \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitPipe(void);

/************************************************************************/
/** \brief Receive and process messages
**
**  \par Description
**       This function receives and processes messages
**       for the EA application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   iBlocking    A #CFE_SB_PEND_FOREVER, #CFE_SB_POLL or
**                             millisecond timeout
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_RcvMsg            \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_RcvMsg(int32 iBlocking);

/************************************************************************/
/** \brief Receive and process messages TODO
**
**  \par Description
**       This function receives and processes messages
**       for the EA application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   iBlocking    A #CFE_SB_PEND_FOREVER, #CFE_SB_POLL or
**                             millisecond timeout
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_RcvMsg            \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_StartApp(CFE_SB_Msg_t* MsgPtr);

/************************************************************************/
/** \brief Receive and process messages TODO
**
**  \par Description
**       This function receives and processes messages
**       for the EA application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   iBlocking    A #CFE_SB_PEND_FOREVER, #CFE_SB_POLL or
**                             millisecond timeout
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_RcvMsg            \endcode
**  \endreturns
**
*************************************************************************/
void  EA_TermApp(CFE_SB_Msg_t* MsgPtr);

/************************************************************************/
/** \brief Receive and process messages TODO
**
**  \par Description
**       This function receives and processes messages
**       for the EA application
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   iBlocking    A #CFE_SB_PEND_FOREVER, #CFE_SB_POLL or
**                             millisecond timeout
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_RcvMsg            \endcode
**  \endreturns
**
*************************************************************************/
void  EA_Perfmon(void);

/************************************************************************/
/** \brief Sends EA housekeeping message
**
**  \par Description
**       This function sends the housekeeping message
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  EA_ReportHousekeeping(void);

/************************************************************************/
/** \brief Sends EA output data
**
**  \par Description
**       This function publishes the EA application output data.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void  EA_SendOutData(void);

/************************************************************************/
/** \brief Verify Command Length
**
**  \par Description
**       This function verifies the command message length.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]   MsgPtr        A #CFE_SB_Msg_t pointer that
**                              references the software bus message
**  \param [in]   usExpectedLen The expected length of the message
**
**  \returns
**  TRUE if the message length matches expectations, FALSE if it does not.
**  \endreturns
**
*************************************************************************/
boolean  EA_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen);

/* TODO:  Add Doxygen markup. */
void EA_ProcessNewData(void);
void EA_ProcessNewCmds(void);
void EA_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr);

/* TODO:  Add a section for global externals. */
extern EA_AppData_t  EA_AppData;



#ifdef __cplusplus
}
#endif 

#endif /* EA_APP_H */

/************************/
/*  End of File Comment */
/************************/
