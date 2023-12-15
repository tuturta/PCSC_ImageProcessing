# cmake_minimum_required(VERSION 3.5)
# project(PCSC-Proj)

# set(CMAKE_CXX_STANDARD 20)

# set(SOURCES test_image.cpp src/Pixel.cpp src/Image.cpp)
# add_executable(test_Image ${SOURCES})

cmake_minimum_required (VERSION 3.3)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 20)


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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
add_library(Transform
  src/transform.cpp
)
# Add the path to Eigen headers
include_directories(${CMAKE_SOURCE_DIR}/eigen)

add_library(Compute
  src/compute.cpp
)

add_subdirectory(googletest)
include_directories(${CMAKE_SOURCE_DIR}/eigen)

# For gnuplot :
# find dependencies (Boost)
find_package(Boost REQUIRED COMPONENTS 
            iostreams system filesystem)
# adds the search path for includes
include_directories(gnuplot-iostream)
add_executable(example_histogram tests/test_histogram.cpp)
# adds linked libraries to produce executable
target_link_libraries(example_histogram PUBLIC Image Pixel Reader PRIVATE
                      Boost::iostreams
                      Boost::system
                      Boost::filesystem
)

# For TESTS 
add_executable(example_compute tests/test_compute.cpp)
target_link_libraries(example_compute PUBLIC Reader Image Pixel Compute gtest_main gtest pthread)

add_executable(test_image tests/test_image.cpp)
target_link_libraries(test_image Image Pixel gtest_main gtest pthread) 

add_executable(test_pixel tests/test_pixels.cpp)
target_link_libraries(test_pixel Pixel gtest_main gtest pthread)

# add_executable(test_writer tests/test_writer.cpp)
# target_link_libraries(test_writer Pixel Image Reader Writer)

add_executable(test_FT tests/test_FT.cpp)
target_link_libraries(test_FT Transform)


#add_custom_target(test ./test_image DEPENDS test_pixel)