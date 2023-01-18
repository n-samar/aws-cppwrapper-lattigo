# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

file(GLOB CPP ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)

target_sources(latticpp_obj
    PRIVATE
        ${CPP}
)

install(
    FILES
        ${HEADERS}
    DESTINATION
        ${LATTICPP_INCLUDES_INSTALL_DIR}/ckks
)
