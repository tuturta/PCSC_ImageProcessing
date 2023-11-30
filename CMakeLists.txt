cmake_minimum_required(VERSION 3.5)
project(PCSC-Proj)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES test_pixels.cpp src/Pixel.cpp)
add_executable(test3 ${SOURCES})

