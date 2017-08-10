#include "ea_custom_test.h"
#include "ea_cmds_test.h"
#include "ea_test_utils.h"
#include "ea_msg.h"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"

char APP_PATH[OS_MAX_PATH_LEN] = "/usr/bin/python";
char TEST_ARG[OS_MAX_PATH_LEN] = "sleep.py";

int32 EA_Cmds_Test_UT_CFE_SB_SubscribeHook1(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 5;
}


int32 EA_Cmds_Test_UT_CFE_SB_SubscribeHook2(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId,
                                                CFE_SB_Qos_t Quality, uint16 MsgLim)
{
    return 6;
}

//printf("%i\n", Ut_CFE_EVS_GetEventQueueDepth());
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CHILD_TASK_START_EID, CFE_EVS_DEBUG, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_APP_ARG_ERR_EID, CFE_EVS_ERROR, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CHILD_TASK_START_ERR_EID, CFE_EVS_ERROR, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CMD_RESET_EID, CFE_EVS_INFORMATION, ""));


/**
 * Test EA_StartAppCustom(), Register Child Task Error
 */
void Test_EA_Custom_StartApp_RegisterChildTaskError(void)
{
    /* Set to cause message "StartApp Child Task Registration failed!" to be printed */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_REGISTERCHILDTASK_INDEX, -1, 1);

    /* Execute the function being tested */
    EA_StartAppCustom();
    
    /* Verify results */
    /* Note: Cannot verify line OS_printf("StartApp Child Task Registration failed!\n") */
    UtAssert_True (EA_AppData.ChildAppTaskID == 0, "Child task ID = 0");
    UtAssert_True (EA_AppData.ChildAppTaskInUse == FALSE, "Child task not in use");
	UtAssert_True(EA_AppData.HkTlm.usCmdErrCnt==1,"Command Error Count = 1");
}

/**
 * Test EA_StartAppCustom(), Invalid App Path
 */
void Test_EA_Custom_StartApp_InvalidAppPath(void)
{
	/* Set to cause execvp to fail */
	EA_AppData.ChildData.AppInterpreter = "InvalidDirectory";

	/* Execute the function being tested */
	EA_StartAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
}

/**
 * Test EA_StartAppCustom(), Failed fork TODO
 */
void Test_EA_Custom_StartApp_FailFork(void)
{
	/* Set to cause fork to fail */


	/* Execute the function being tested */
	EA_StartAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
	UtAssert_True(EA_AppData.HkTlm.usCmdErrCnt==1,"Command Error Count = 1");
}

/**
 * Test EA_StartAppCustom(), Nominal
 */
void Test_EA_Custom_StartApp_Nominal(void)
{
	EA_AppData.ChildData.AppInterpreter = APP_PATH;
	EA_AppData.ChildData.AppSript = ;

	/* Execute the function being tested */
	EA_StartAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
	UtAssert_True(EA_AppData.HkTlm.usCmdCnt==0,"Command Count = 0"); 
}

/**
 * Test EA_StartAppCustom(), 
 */
void Test_EA_Custom_StartApp_(void)
{

	/* Execute the function being tested */
	EA_StartAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
	UtAssert_True(EA_AppData.HkTlm.usCmdCnt==0,"Command Count = 0"); 
}


/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void EA_Custom_Test_AddTestCases(void)
{
    UtTest_Add(Test_EA_Custom_StartApp_RegisterChildTaskError, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_StartApp_RegisterChildTaskError");
    UtTest_Add(Test_EA_Custom_StartApp_InvalidAppPath, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_StartApp_InvalidAppPath");
    //UtTest_Add(, EA_Test_Setup, EA_Test_TearDown, "");
    //UtTest_Add(, EA_Test_Setup, EA_Test_TearDown, "");
}

