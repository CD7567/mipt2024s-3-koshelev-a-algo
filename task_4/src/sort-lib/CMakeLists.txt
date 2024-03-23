cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(sort-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        SORT_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file(
        GLOB_RECURSE
        SORT_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        sort-lib
        ${SORT_LIB_HEADERS}
        ${SORT_LIB_SOURCES}
)

target_include_directories(
        sort-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(sort-lib PROPERTIES LINKER_LANGUAGE CXX)
