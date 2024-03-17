cmake_minimum_required(VERSION 3.10)

project(MergeSortedArray
  VERSION
    1.0
  DESCRIPTION
    "Merge sorted array implementation"
  LANGUAGES
    CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(mergesortedarray_test src/TwoSortedArrays.cpp)

add_custom_command(
    TARGET mergesortedarray_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/mergesortedarray_test
    DEPENDS mergesortedarray_test
    COMMENT "Running mergesortedarray example test"
)