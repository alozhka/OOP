cmake_minimum_required(VERSION 3.28)
project(invert)

set(CMAKE_CXX_STANDARD 20)

add_executable(invert main.cpp lib/Matrix.cpp)
