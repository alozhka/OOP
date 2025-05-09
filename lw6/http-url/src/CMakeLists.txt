add_library(lib_http_url STATIC
        Protocol.h
        CHttpUrl.cpp
        CHttpUrl.h)

target_include_directories(lib_http_url PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})