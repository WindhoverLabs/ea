
#include "uttest.h"

#include "ea_app_test.h"
#include "ea_cmds_test.h"
#include "ea_config_tbl_test.h"
#include "ea_cds_tbl_test.h"

int main(void)
{   
    EA_App_Test_AddTestCases();
    EA_Cmds_Test_AddTestCases();
    EA_Config_Tbl_Test_AddTestCases();
    EA_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

