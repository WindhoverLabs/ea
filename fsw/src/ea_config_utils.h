    
#ifndef EA_CONFIG_UTILS_H
#define EA_CONFIG_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "ea_app.h"

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
/** \brief Init EA Config table
**
**  \par Description
**       This function initializes EA's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \retstmt Return codes from #CFE_TBL_Register          \endcode
**  \retstmt Return codes from #CFE_TBL_Load              \endcode
**  \retstmt Return codes from #EA_AcquireConfigPointers \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_InitConfigTbl(void);

/************************************************************************/
/** \brief Validate EA Config table
**
**  \par Description
**       This function validates EA's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32  EA_ValidateConfigTbl(void*);

/************************************************************************/
/** \brief Obtain EA Config Table Data Pointer
**
**  \par Description
**       This function manages the config table
**       and obtains a pointer to its data.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32 EA_AcquireConfigPointers(void);

/************************************************************************/
/** \brief Process new EA Config table
**
**  \par Description
**       This function processes EA's new Config table
**       and set Config parameters with new values.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
void   EA_ProcessNewConfigTbl(void);


#ifdef __cplusplus
}
#endif

#endif /* EA_CONFIG_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
