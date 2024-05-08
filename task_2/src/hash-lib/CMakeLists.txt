cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(hash-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        HASH_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        hash-lib
        ${HASH_LIB_HEADERS}
)

target_link_libraries(
        hash-lib PUBLIC
        memory-lib
)

target_include_directories(
        hash-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(hash-lib PROPERTIES LINKER_LANGUAGE CXX)
