
#ifndef EA_TEST_UTILS_H
#define EA_TEST_UTILS_H

/*
 * Includes
 */

#include "ea_app.h"

extern EA_AppData_t  EA_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void EA_Test_Setup(void);
void EA_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* EA_TEST_UTILS_H */

