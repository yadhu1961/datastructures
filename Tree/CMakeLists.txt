cmake_minimum_required(VERSION 3.10)

project(BinaryTree
  VERSION
    1.0
  DESCRIPTION
    "Binary Tree implementation"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(binarytree_test src/BinaryTree_driver.cpp)

add_compile_options(-Wall -Wextra -Wpedantic, -fpermissive, -g)

add_custom_command(
    TARGET binarytree_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/binarytree_test
    DEPENDS binarytree_test
    COMMENT "Running binary tree example implementation test"
)