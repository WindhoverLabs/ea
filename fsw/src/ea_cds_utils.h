
#ifndef EA_CDS_UTILS_H
#define EA_CDS_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "ea_tbldefs.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief Init EA CDS tables
**
**  \par Description
**       This function initializes EA's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_ES_RegisterCDS       \endcode
**  \retstmt Return codes from #CFE_ES_CopyToCDS         \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitCdsTbl(void);

/************************************************************************/
/** \brief Update EA CDS tables
**
**  \par Description
**       This function updates EA's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   EA_UpdateCdsTbl(void);

/************************************************************************/
/** \brief Save EA CDS tables
**
**  \par Description
**       This function saves EA's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   EA_SaveCdsTbl(void);


#ifdef __cplusplus
}
#endif
 
#endif /* EA_CDS_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    