cmake_minimum_required(VERSION 3.30)
project(shapes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SFML
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

set(SOURCES main.cpp
        include/IShape.h
        include/ISolidShape.h
        include/CTriangle.h
        source/CPoint.cpp
        source/CTriangle.cpp
        source/CLineSegment.cpp
        source/CRectangle.cpp
        include/CRectangle.h
        source/CCircle.cpp
        include/CCircle.h
        include/ICanvas.h
        include/ICanvasDrawable.h
        source/CCanvas.cpp
        include/CCanvas.h
        source/CShapesController.cpp
        include/CShapesController.h)

# shapes
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SFML::Graphics)

# tests
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
        tests/tests.cpp
        tests/CMockCanvas.h
        tests/CMockCanvas.cpp
        include/IShape.h
        include/ISolidShape.h
        include/CTriangle.h
        source/CPoint.cpp
        source/CTriangle.cpp
        source/CLineSegment.cpp
        source/CRectangle.cpp
        include/CRectangle.h
        source/CCircle.cpp
        include/CCircle.h
        include/ICanvas.h
        include/ICanvasDrawable.h)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)