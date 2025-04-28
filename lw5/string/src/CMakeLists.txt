add_library(libstring STATIC CString.cpp)

target_include_directories(libstring PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})