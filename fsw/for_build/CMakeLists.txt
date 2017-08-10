
add_airliner_app_def(ea
    FILE EA
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

	USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
)

add_airliner_app_unit_test(ea-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cds_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_config_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_custom_stub.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

add_custom_target(
    ea-ut-input-files
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sleep.py ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fib.py ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(ea-ut ea-ut-input-files)
