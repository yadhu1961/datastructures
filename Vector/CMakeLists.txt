cmake_minimum_required(VERSION 3.10)

project(Vector
  VERSION
    1.0
  DESCRIPTION
    "Vector implementation"
  LANGUAGES
    CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(vector_test src/Vector_driver.cpp)

add_compile_options(-Wall -Wextra -Wpedantic, -fpermissive, -g)

add_custom_command(
    TARGET vector_test
    POST_BUILD
    COMMAND bin/vector_test
    DEPENDS vector_test
    COMMENT "Running Custom Vector example implementation test"
)