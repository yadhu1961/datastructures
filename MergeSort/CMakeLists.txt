cmake_minimum_required(VERSION 3.10)

project(MergeSort
  VERSION
    1.0
  DESCRIPTION
    "Merge sort implementation"
  LANGUAGES
    CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(mergesort_test src/MergeSort.cpp)

add_custom_command(
    TARGET mergesort_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/mergesort_test
    DEPENDS mergesort_test
    COMMENT "Running mergesort example test"
)