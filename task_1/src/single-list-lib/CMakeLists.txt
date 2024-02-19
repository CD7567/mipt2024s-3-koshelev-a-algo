cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(single-list-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        SINGLE_LIST_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        single-list-lib
        ${SINGLE_LIST_LIB_HEADERS}
)

target_include_directories(
        single-list-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(single-list-lib PROPERTIES LINKER_LANGUAGE CXX)