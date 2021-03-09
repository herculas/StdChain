cmake_minimum_required(VERSION 3.17)
project(stdchain)

# Conan packages
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake does not exist, run conan install first.")
endif ()

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

aux_source_directory(src/core/block CORE_BLOCK)
aux_source_directory(src/core/script CORE_SCRIPT)
aux_source_directory(src/core/transaction CORE_TRANS)
aux_source_directory(src/type/blob TYPE_BLOB)
aux_source_directory(src/util/encode UTIL_ENCODE)

add_executable(
        stdchain
        main.cpp
        ${CORE_BLOCK}
        ${CORE_SCRIPT}
        ${CORE_TRANS}

        ${TYPE_BLOB}
        
        ${UTIL_ENCODE}
)

# import
find_package(OpenSSL REQUIRED)
find_package(Boost 1.75.0 COMPONENTS program_options serialization REQUIRED)
target_link_libraries(
        stdchain
        PUBLIC  OpenSSL::SSL
                Boost::program_options
                Boost::serialization
)
