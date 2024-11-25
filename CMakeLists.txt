cmake_minimum_required(VERSION 3.16)

project(SQLito VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/examples)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set(EXAMPLES_BUILD_DIR ${BUILD_DIR}/examples)
set(TESTS_BUILD_DIR ${BUILD_DIR}/tests)

if(NOT EXISTS ${EXAMPLES_BUILD_DIR})
    file(MAKE_DIRECTORY ${EXAMPLES_BUILD_DIR})
endif()

if(NOT EXISTS ${TESTS_BUILD_DIR})
    file(MAKE_DIRECTORY ${TESTS_BUILD_DIR})
endif()

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_LIBRARY "Build library" ON)

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h" "${SRC_DIR}/*.hpp")

if(BUILD_LIBRARY)
    add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
    target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
endif()

if(BUILD_EXAMPLES AND EXISTS ${EXAMPLES_DIR})
    file(GLOB EXAMPLES "${EXAMPLES_DIR}/*.cpp")
    foreach(EXAMPLE ${EXAMPLES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE})
        target_include_directories(${EXAMPLE_NAME} PUBLIC ${INCLUDE_DIR})
        target_link_libraries(${EXAMPLE_NAME} ${PROJECT_NAME})
        set_target_properties(${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXAMPLES_BUILD_DIR})
    endforeach()
endif()

if(BUILD_TESTS AND EXISTS ${TEST_DIR})
    enable_testing()
    file(GLOB TESTS "${TEST_DIR}/*.cpp")
    foreach(TEST ${TESTS})
        get_filename_component(TEST_NAME ${TEST} NAME_WE)
        add_executable(${TEST_NAME} ${TEST})
        target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIR})
        target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
        set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_BUILD_DIR})
    endforeach()
endif()