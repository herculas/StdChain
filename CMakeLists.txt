cmake_minimum_required(VERSION 3.17)
project(stdchain)

# Conan packages setup
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake does not exist, run conan install first.")
endif ()

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

aux_source_directory(src/core/block CORE_BLOCK)
aux_source_directory(src/core/chain CORE_CHAIN)
aux_source_directory(src/core/coin CORE_COIN)
aux_source_directory(src/core/script CORE_SCRIPT)
aux_source_directory(src/core/transaction CORE_TRANS)

aux_source_directory(src/process/transaction PROC_TRANS)
aux_source_directory(src/process/consensus PROC_CONS)

aux_source_directory(src/type/arith TYPE_ARITH)
aux_source_directory(src/type/blob TYPE_BLOB)
aux_source_directory(src/type/file TYPE_FILE)

aux_source_directory(src/util/concurrent UTIL_CONC)
aux_source_directory(src/util/encode UTIL_ENCODE)
aux_source_directory(src/util/hash UTIL_HASH)
aux_source_directory(src/util/random UTIL_RAND)

add_executable(
        stdchain
        main.cpp

        ${CORE_BLOCK}
        ${CORE_CHAIN}
        ${CORE_COIN}
        ${CORE_SCRIPT}
        ${CORE_TRANS}

        ${PROC_TRANS}
        ${PROC_CONS}

        ${TYPE_ARITH}
        ${TYPE_BLOB}
        ${TYPE_FILE}

        ${UTIL_CONC}
        ${UTIL_ENCODE}
        ${UTIL_HASH}
        ${UTIL_RAND}
)

# link libraries from Conan
target_link_libraries(stdchain ${CONAN_LIBS})