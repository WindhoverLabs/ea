
add_airliner_app_def(ea
    FILE EA
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_private_ids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_serialization.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_serialization.h
        ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf/ea_start.pb.c
        ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf/ea_start.pb.h
   
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        
    PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/proto_defs/ea_start.proto

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(ea-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cds_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cds_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_config_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_custom_stub.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_custom_stub.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/ea_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_cds_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_config_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_private_ids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/ea_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

add_custom_target(
    ea-ut-input-files
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sleep.py ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/fib.py ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/noop.py ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(ea-ut ea-ut-input-files)

