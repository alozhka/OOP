cmake_minimum_required(VERSION 3.28)
project(radix)

set(CMAKE_CXX_STANDARD 26)

# Tests
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/unit_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
# Radix
add_executable(radix main.cpp)
