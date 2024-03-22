cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(list-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        LIST_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        list-lib
        ${LIST_LIB_HEADERS}
)

target_include_directories(
        list-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(list-lib PROPERTIES LINKER_LANGUAGE CXX)
