#ifndef EA_CUSTOM_H
#define EA_CUSTOM_H

/*************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
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
/** \brief Initialize Child task and start external application
**
**  \par Description
**       This function spawns a CFS child task that will then call the
**       external application. The child task will perform a fork, with
**       the child of the fork executing the specified app and the
**       parent waiting for the child to finish execution. If the fork's
**       child task completes the parent will capture its return code
**       and update all relevant HK telemetry.
**
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void EA_StartAppCustom();

void EA_TermAppCustom(CFE_SB_Msg_t* MsgPtr);
void EA_PerfmonCustom(int32 pid);

#endif
