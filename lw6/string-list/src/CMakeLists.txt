add_library(lib_string_list STATIC
        CStringList.cpp
        CStringList.h
        CStringListIterators.cpp)

target_include_directories(lib_string_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})