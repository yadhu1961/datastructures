cmake_minimum_required(VERSION 3.10)

project(CircularLinkedList
  VERSION
    1.0
  DESCRIPTION
    "Circular Linked list implementation"
  LANGUAGES
    CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(circularlinkedlist_test src/CircularLinkedList.cpp)

add_custom_command(
    TARGET circularlinkedlist_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/circularlinkedlist_test
    DEPENDS circularlinkedlist_test
    COMMENT "Running CircularLinkedList example implementation test"
)