cmake_minimum_required(VERSION 3.10)

project(DataStructures
  VERSION
    1.0
  DESCRIPTION
    "DataStructures implementation"
  LANGUAGES
    CXX
)

add_subdirectory(LinkedList LinkedList/bin)
add_subdirectory(Queue Queue/bin)
add_subdirectory(Stack Stack/bin)
add_subdirectory(Vector Vector/bin)
add_subdirectory(Tree Tree/bin)
add_subdirectory(LRU_Cache LRU_Cache/bin)