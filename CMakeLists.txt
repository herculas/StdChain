cmake_minimum_required(VERSION 3.17)
project(stdchain)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

aux_source_directory(src/core CORE)
aux_source_directory(src/type SELF_DEFINED_TYPE)
aux_source_directory(src/util/compact COMPACT)
aux_source_directory(src/util/encode ENCODE)
aux_source_directory(src/util/hash HASH)

add_executable(
        stdchain
        main.cpp
        ${CORE}
        ${SELF_DEFINED_TYPE}
        ${HASH}
        ${COMPACT}
        ${ENCODE}
)
