#ifndef EA_CUSTOM_H
#define EA_CUSTOM_H

/*************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#ifdef EA_MOCK_OS_CALLS_H
#include "ea_mock_os_calls.c"
#endif
#include <unistd.h>

/*************************************************************************
** Custom Global Data Structure
*************************************************************************/

/**
**  \brief Data required to calculate external application utilization
*/
typedef struct
{
	/** \brief Total system cpu time (in jiffies) */
    unsigned long long int			total_time;

    /** \brief Total  cpu time (in jiffies) */
    unsigned long long int			p_time;

} EA_ProcData_t;

/************************************************************************/
/** \brief Initialize Child Task and Start External Application
**
**  \par Description
**       This function spawns a CFS child task that will then call the
**       external application. The child task will perform a fork, with
**       the child of the fork executing the specified app and the
**       parent waiting for the child to finish execution. If the fork's
**       child task completes the parent will capture its return code
**       and update all relevant HK telemetry.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void EA_StartAppCustom();

/************************************************************************/
/** \brief Terminate Child task and Stop External Application
**
**  \par Description
**       This function kills the CFS child task and the external 
**       application. The HK telemetry for ActiveApp is copied to 
**       LastRunApp and LastAppStatus is set to -1. All other relevant
**       HK telemetry is reset to default values
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void EA_TermAppCustom();

/************************************************************************/
/** \brief Performance Monitoring
**
**  \par Description
**       This function uses a helper function to calculate the CPU
**       utilization of the external application. Once the helper returns
**       HK telemetry is updated to current value.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void EA_PerfmonCustom(int32 pid);

/************************************************************************/
/** \brief Initialize Child task and start external application
**
**  \par Description
**       This function reads from the proc tree and calculates the 
**       percentage of the CPU time the app is using. EA_APP_NUM_THREADS
**       in platform config needs to be set to the correct amount of
**       threads the app will run on for util to be a valid number 
**       between 0-100.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
EA_ProcData_t EA_ParsePidUtil(int32 pid);

#endif
