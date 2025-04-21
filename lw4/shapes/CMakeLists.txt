cmake_minimum_required(VERSION 3.30)
project(shapes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SFML
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${CMAKE_PROJECT_NAME} main.cpp
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
        source/CCanvas.cpp
        include/CCanvas.h
        source/CShapesController.cpp
        include/CShapesController.h)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SFML::Graphics)