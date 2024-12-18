cmake_minimum_required(VERSION 3.16)

project(sqlito)

message(STATUS "compiler: " ${CMAKE_CXX_COMPILER_ID})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_EXAMPLES "Compilar ejemplos de la librería" OFF)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/lib/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/lib/inc")
set(EXP_DIR "${CMAKE_SOURCE_DIR}/examples")

include_directories("${INC_DIR}")
set(SRC_FILES
    "${SRC_DIR}/sqlito.cpp"
    "${SRC_DIR}/Disk.cpp"
    "${SRC_DIR}/DiskManager.cpp"
    "${SRC_DIR}/utils/File.cpp"
)

add_library(sqlito STATIC ${SRC_FILES})

if(BUILD_EXAMPLES)
    add_subdirectory("${EXP_DIR}")
endif()