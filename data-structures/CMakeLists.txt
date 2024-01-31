add_library(linked-lists STATIC
linked-lists.cpp
linked-lists.h)

target_include_directories(linked-lists PRIVATE ${CMAKE_CURRENT_LIST_DIR})