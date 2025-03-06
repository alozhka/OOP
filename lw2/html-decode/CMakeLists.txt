cmake_minimum_required(VERSION 3.30)
project(html_decode)

set(CMAKE_CXX_STANDARD 20)

# Tests
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/unit_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)

add_executable(html_decode main.cpp lib/HtmlDecoder.cpp)
