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
aux_source_directory(src/type/blob TYPE_BLOB)

add_executable(
        stdchain
        main.cpp
        ${CORE_BLOCK}
        ${TYPE_BLOB}
)

# openssl import
find_package(OpenSSL REQUIRED)
target_link_libraries(stdchain OpenSSL::SSL)
