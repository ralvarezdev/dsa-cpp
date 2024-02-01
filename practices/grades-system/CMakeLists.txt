cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(GradesSystem LANGUAGES CXX)

add_executable(${PROJECT_NAME} ./src/main.cpp)

add_library(linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/linked-lists/base.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/students)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/students
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE terminal
  PRIVATE students
  PRIVATE linked-lists
)