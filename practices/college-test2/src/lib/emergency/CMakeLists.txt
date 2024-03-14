add_library(emergency STATIC
emergency.h
emergency.cpp)

target_include_directories(emergency PRIVATE ${CMAKE_CURRENT_LIST_DIR})