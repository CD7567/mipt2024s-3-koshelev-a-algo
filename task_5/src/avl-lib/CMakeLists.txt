cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(avl-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        AVL_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        avl-lib
        ${AVL_LIB_HEADERS}
)

target_link_libraries(
        avl-lib PUBLIC
        memory-lib
)

target_include_directories(
        avl-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(avl-lib PROPERTIES LINKER_LANGUAGE CXX)
