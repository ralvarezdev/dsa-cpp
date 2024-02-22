cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(number LANGUAGES CXX)

add_executable(${PROJECT_NAME} ./src/main.cpp)

add_library(circular-doubly-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../circular-doubly-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../circular-doubly-linked-lists/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../circular-doubly-linked-lists/number.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../circular-doubly-linked-lists/number.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes/doublyNode.h
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE circular-doubly-linked-lists
)