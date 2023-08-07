cmake_minimum_required(VERSION 3.10)

project(Queue
  VERSION
    1.0
  DESCRIPTION
    "Queue implementation"
  LANGUAGES
    CXX
)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(queue_driver_test src/Queue_driver.cpp)

target_compile_options(queue_driver_test PRIVATE -std=c++17 -Wall -Wextra -Wpedantic -fpermissive -g)

add_custom_command(
    TARGET queue_driver_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/queue_driver_test
    DEPENDS queue_driver_test
    COMMENT "Running queue example implementation test"
)