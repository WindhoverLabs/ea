#include "ea_app.h"
#include "ea_custom.h"
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
#include "ea_mock_os_calls.h"

//printf("%i\n", Ut_CFE_EVS_GetEventQueueDepth());
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CHILD_TASK_START_EID, CFE_EVS_DEBUG, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_APP_ARG_ERR_EID, CFE_EVS_ERROR, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CHILD_TASK_START_ERR_EID, CFE_EVS_ERROR, ""));
//printf("%i\n", Ut_CFE_EVS_GetEventCount(EA_CMD_RESET_EID, CFE_EVS_INFORMATION, ""));
//printf("%i\n", EA_AppData.HkTlm.usCmdErrCnt);
//printf("%i\n", EA_AppData.HkTlm.usCmdCnt);

char CUSTOM_APP_PATH[OS_MAX_PATH_LEN] = "/usr/bin/python";
char CUSTOM_TEST_ARG[OS_MAX_PATH_LEN] = "noop.py";

int FORK_RET_CODE;
int EXECVP_RET_CODE;
int KILL_RET_CODE;

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
}

/**
 * Test EA_StartAppCustom(), Invalid App Path
 */
void Test_EA_Custom_StartApp_InvalidAppPath(void)
{
	/* Set to cause execvp to fail */
	//strncpy(EA_AppData.ChildData.AppInterpreter, "InvalidDirectory", OS_MAX_PATH_LEN);
	FORK_RET_CODE = 13;
	EXECVP_RET_CODE = -1;

	/* Execute the function being tested */
	EA_StartAppCustom();

	printf("Test: %i\n", EA_AppData.HkTlm.usCmdCnt);
	/* Verify results */
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
	UtAssert_True (EA_AppData.HkTlm.ActiveAppPID == 0, "Active App PID = 0");
	UtAssert_True (EA_AppData.ChildAppTaskID == 0, "Child task ID = 0");
    UtAssert_True (EA_AppData.ChildAppTaskInUse == FALSE, "Child task not in use");
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
	strncpy(EA_AppData.ChildData.AppInterpreter, CUSTOM_APP_PATH, OS_MAX_PATH_LEN);
	strncpy(EA_AppData.ChildData.AppScript, CUSTOM_TEST_ARG, OS_MAX_PATH_LEN);

	/* Execute the function being tested */
	EA_StartAppCustom();
	//printf("%i\n", Ut_CFE_EVS_GetEventQueueDepth());
	//printf("%i\n", EA_AppData.HkTlm.usCmdCnt);

	/* Verify results */
	//UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1"); // TODO
	//UtAssert_EventSent(EA_INF_APP_START_EID, CFE_EVS_INFORMATION, "External application started", "External application started");
	UtAssert_True(EA_AppData.HkTlm.usCmdCnt==1,"Command Count = 1"); 
}

/**
 * Test EA_TermAppCustom(), No app running
 */
void Test_EA_Custom_TermApp_NoneActive(void)
{
	EA_AppData.HkTlm.ActiveAppPID = 0;

	/* Execute the function being tested */
	EA_TermAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Attempted to terminate app while none executing", "No active app");
	UtAssert_True(EA_AppData.HkTlm.usCmdErrCnt==1,"Command Error Count = 1"); 
}

/**
 * Test EA_TermAppCustom(), Failed kill TODO
 */
void Test_EA_Custom_TermApp_(void)
{
	EA_StartAppCustom();

	/* Execute the function being tested */
	EA_TermAppCustom();

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_CMD_ERR_EID, CFE_EVS_ERROR, 
						"Error starting external application", "Error starting external application");
	UtAssert_True(EA_AppData.HkTlm.usCmdCnt==0,"Command Count = 0");
}

/**
 * Test EA_TermAppCustom(), Nominal
 */
void Test_EA_Custom_TermApp_Nominal(void)
{
	/* Set active app params that TermApp will clear or copy to last app params */
	//strncpy(EA_AppData.HkTlm.ActiveApp, "Active External App", OS_MAX_PATH_LEN);
	//EA_AppData.HkTlm.ActiveAppPID = 1;
	//EA_AppData.HkTlm.ActiveAppUtil = 2;
	//EA_AppData.ChildAppTaskInUse = TRUE;
	strncpy(EA_AppData.ChildData.AppInterpreter, CUSTOM_APP_PATH, OS_MAX_PATH_LEN);
	strncpy(EA_AppData.ChildData.AppScript, CUSTOM_TEST_ARG, OS_MAX_PATH_LEN);

	/* Execute the function being tested */
	EA_StartAppCustom();
	/* Execute the function being tested */
	EA_TermAppCustom();

	printf("%s\n", EA_AppData.HkTlm.LastAppRun);
	printf("%i\n", Ut_CFE_EVS_GetEventQueueDepth());

	/* Verify results */
	UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
	UtAssert_EventSent(EA_INF_APP_TERM_EID, CFE_EVS_INFORMATION,"", "External application terminated");
	UtAssert_True(EA_AppData.HkTlm.usCmdCnt==1,"Command Count = 1");
	UtAssert_True(EA_AppData.HkTlm.ActiveAppPID==0,"ActiveAppPID = 0");
	UtAssert_True(EA_AppData.HkTlm.ActiveAppUtil==0,"ActiveAppUtil = 0");//
	UtAssert_True(EA_AppData.ChildAppTaskInUse==FALSE,"ChildAppTaskInUse = FALSE");
	UtAssert_StrCmp(EA_AppData.HkTlm.LastAppRun, CUSTOM_APP_PATH, "Last Active App set");
}

/**************************************************************************
 * Rollup Test Cases
 **************************************************************************/
void EA_Custom_Test_AddTestCases(void)
{
    UtTest_Add(Test_EA_Custom_StartApp_RegisterChildTaskError, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_StartApp_RegisterChildTaskError");
    UtTest_Add(Test_EA_Custom_StartApp_InvalidAppPath, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_StartApp_InvalidAppPath");
    UtTest_Add(Test_EA_Custom_StartApp_Nominal, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_StartApp_Nominal");
    UtTest_Add(Test_EA_Custom_TermApp_NoneActive, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_TermApp_NoneActive");
	UtTest_Add(Test_EA_Custom_TermApp_Nominal, EA_Test_Setup, EA_Test_TearDown, "Test_EA_Custom_TermApp_Nominal");
	//UtTest_Add(, EA_Test_Setup, EA_Test_TearDown, "");
	//UtTest_Add(, EA_Test_Setup, EA_Test_TearDown, "");
}

