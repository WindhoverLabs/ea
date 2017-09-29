#############################################################################
#
#   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name Windhover Labs nor the names of its 
#    contributors may be used to endorse or promote products derived 
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################
 
set(EA_PROTOBUF_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf)

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
        ${EA_PROTOBUF_MSGS_DIR}/ea_start.pb.c
        ${EA_PROTOBUF_MSGS_DIR}/ea_start.pb.h
   
    INCLUDES
        ${EA_PROTOBUF_MSGS_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        
    PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/ea_start.proto
        
    PROTOBUF_MSGS_DIR        
        ${EA_PROTOBUF_MSGS_DIR}

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
        ${EA_PROTOBUF_MSGS_DIR}
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

set(EA_PROTOBUF_MSGS_DIR ${EA_PROTOBUF_MSGS_DIR} PARENT_SCOPE)
