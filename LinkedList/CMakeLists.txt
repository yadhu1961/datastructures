cmake_minimum_required(VERSION 3.10)

project(Crtp
  VERSION
    1.0
  DESCRIPTION
    "Linked list implementation"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(linkedlist_test src/LinkedList_driver.cpp)

add_custom_command(
    TARGET linkedlist_test
    POST_BUILD
    COMMAND bin/linkedlist_test
    DEPENDS linkedlist_test
    COMMENT "Running LinkedList example implementation test"
)