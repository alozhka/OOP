add_library(lib_string_list STATIC
        CStringList.cpp
        CStringList.h
        CIterator.cpp
        CIterator.h)

target_include_directories(lib_string_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})