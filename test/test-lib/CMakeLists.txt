cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(test-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        TEST_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file(
        GLOB_RECURSE
        TEST_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

find_package(doctest REQUIRED)

add_library(
        test-lib
        ${TEST_LIB_HEADERS}
        ${TEST_LIB_SOURCES}
)

target_include_directories(
        test-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(
        test-lib PUBLIC
        doctest::doctest
        list-lib
        hash-lib
        memory-lib
        sort-lib
        avl-lib
)

set_target_properties(test-lib PROPERTIES LINKER_LANGUAGE CXX)
