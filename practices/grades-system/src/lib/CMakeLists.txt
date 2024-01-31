add_library(lib STATIC
students.cpp
students.h)

target_include_directories(lib PRIVATE ${CMAKE_CURRENT_LIST_DIR})