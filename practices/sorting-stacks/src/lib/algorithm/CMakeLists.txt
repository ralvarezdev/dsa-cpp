add_library(algorithm STATIC
modHanoi.h
modHanoi.cpp)

target_include_directories(algorithm PRIVATE ${CMAKE_CURRENT_LIST_DIR})