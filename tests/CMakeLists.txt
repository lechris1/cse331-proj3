cmake_minimum_required(VERSION 2.6)
project(cse331_stackbst_project)

################################
# Code
################################
# internal
file(GLOB_RECURSE HW_SOURCES "src/*.cpp")
file(GLOB_RECURSE HW_HEADERS "src/*.h")

set (HW_INCLUDE_DIRS "")
foreach (_headerFile ${HW_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND HW_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES HW_INCLUDE_DIRS)

include_directories(${HW_INCLUDE_DIRS})
# external
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)


# c++11 plz
add_compile_options(-std=c++11 -g -Wall)

################################
# GTest
################################
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test(s) from cpp file(s)

add_executable(tests "tests.cpp")
# Link test executable against gtest & gtest_main

target_link_libraries(tests gtest gtest_main)
add_test(tests tests)
