cmake_minimum_required(VERSION 3.10)

project(Stack
  VERSION
    1.0
  DESCRIPTION
    "Stack implementation"
  LANGUAGES
    CXX
)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(stack_driver_test src/Stack_driver.cpp)

target_compile_options(stack_driver_test PRIVATE -std=c++17 -Wall -Wextra -Wpedantic -fpermissive -g)

add_custom_command(
    TARGET stack_driver_test
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/bin/stack_driver_test
    DEPENDS stack_driver_test
    COMMENT "Running Stack example implementation test"
)