cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(ReadingNumbers LANGUAGES CXX)

add_executable(${PROJECT_NAME} ./src/main.cpp)

add_library(queue SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../queue/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../queue/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../nodes/singleNode.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE queue
  PRIVATE terminal
)