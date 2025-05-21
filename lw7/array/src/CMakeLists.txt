add_library(lib_array STATIC
        MyArray.h
        MyArray.cpp)

target_include_directories(lib_array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})