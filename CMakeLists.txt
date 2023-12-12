# cmake_minimum_required(VERSION 3.5)
# project(PCSC-Proj)

# set(CMAKE_CXX_STANDARD 20)

# set(SOURCES test_image.cpp src/Pixel.cpp src/Image.cpp)
# add_executable(test_Image ${SOURCES})

cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 20)

add_library(Image
  src/Image.cpp
)
add_library(Pixel
  src/Pixel.cpp
)
add_library(Reader
  src/reader.cpp
)
add_library(Writer
  src/writer.cpp
)

# add_subdirectory(googletest)

# add_executable(test_image tests/test_image.cpp)
# target_link_libraries(test_image Image Pixel gtest_main gtest pthread)

# add_executable(test_pixel tests/test_pixels.cpp)
# target_link_libraries(test_pixel Pixel gtest_main gtest pthread)

add_executable(test_writer tests/test_writer.cpp)
target_link_libraries(test_writer Pixel Image Reader Writer)

#add_custom_target(test ./test_image DEPENDS test_pixel)