cmake_minimum_required(VERSION 3.10)

project(LRUCache
  VERSION
    1.0
  DESCRIPTION
    "LRU Cache implementation"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(LRUCache_test src/LRUCache_driver.cpp)

add_compile_options(-Wall -Wextra -Wpedantic, -fpermissive, -g)

add_custom_command(
    TARGET LRUCache_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/LRUCache_test
    DEPENDS LRUCache_test
    COMMENT "Running LRU Cache example implementation test"
)