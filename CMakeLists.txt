cmake_minimum_required(VERSION 3.17)
project(stdchain)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

aux_source_directory(src/core CORE)

aux_source_directory(src/type/blob TYPE_BLOB)
aux_source_directory(src/type/hash TYPE_HASH)
aux_source_directory(src/type/stream TYPE_STREAM)

aux_source_directory(src/util/compact UTIL_COMPACT)
aux_source_directory(src/util/encode UTIL_ENCODE)
aux_source_directory(src/util/hash UTIL_HASH)
aux_source_directory(src/util/serialize UTIL_SERIALIZE)

add_executable(
        stdchain
        main.cpp
        ${CORE}
        ${TYPE_BLOB}
        ${TYPE_HASH}
        ${TYPE_STREAM}
        ${UTIL_COMPACT}
        ${UTIL_ENCODE}
        ${UTIL_HASH}
        ${UTIL_SERIALIZE}
)
