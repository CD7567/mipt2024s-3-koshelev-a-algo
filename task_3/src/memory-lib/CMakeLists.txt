cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(memory-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        MEMORY_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        memory-lib
        ${MEMORY_LIB_HEADERS}
)

target_include_directories(
        memory-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(memory-lib PROPERTIES LINKER_LANGUAGE CXX)
