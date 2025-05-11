add_library(lib_string_list STATIC
        CStringList.cpp
        CStringList.h)

target_include_directories(lib_string_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})