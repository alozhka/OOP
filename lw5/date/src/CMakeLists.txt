add_library(libdate STATIC CDate.cpp)

target_include_directories(libdate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})