cmake_minimum_required(VERSION 3.30)
project(shapes)

set(CMAKE_CXX_STANDARD 20)

add_executable(shapes main.cpp include/IShape.h
        include/ISolidShape.h
        include/CTriangle.h
        source/CPoint.cpp
        source/CTriangle.cpp
        source/CLineSegment.cpp
        source/CRectangle.cpp
        include/CRectangle.h
        source/CCircle.cpp
        include/CCircle.h)
