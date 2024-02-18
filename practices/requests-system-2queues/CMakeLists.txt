cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(RequestsSystem LANGUAGES CXX)

add_executable(${PROJECT_NAME} ./src/main.cpp)

add_library(single-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/single-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/single-linked-lists/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/nodes/singleNode.h
)

add_library(queue SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/queue/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/queue/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data-structures/nodes/singleNode.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/requests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/requests
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/terminal
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE terminal
  PRIVATE requests
  PRIVATE single-linked-lists
  PRIVATE queue
)