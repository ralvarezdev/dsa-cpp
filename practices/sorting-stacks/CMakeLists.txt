cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(SortingStacks LANGUAGES CXX)

add_executable(${PROJECT_NAME} ./src/main.cpp)

add_library(doubly-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/doubly-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/doubly-linked-lists/base.cpp
)

add_library(stack SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/stack/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/stack/base.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE terminal
  PRIVATE doubly-linked-lists
  PRIVATE stack
)