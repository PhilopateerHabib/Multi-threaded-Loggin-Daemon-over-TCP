cmake_minimum_required(VERSION 3.22)
project(ServerApp)

set(CMAKE_CXX_COMPILER ${GPP_RPI4_CROSS_COMPILER})
set(CMAKE_C_COMPILER ${GCC_RPI4_CROSS_COMPILER})

add_subdirectory(src)
