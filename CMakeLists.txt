cmake_minimum_required(VERSION 3.5)
project(PCSC-Proj)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES test_image.cpp src/Pixel.cpp src/Image.cpp)
add_executable(test_Image ${SOURCES})

