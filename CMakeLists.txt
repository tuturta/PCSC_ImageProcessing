cmake_minimum_required (VERSION 3.3)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 20)


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/googletest)
include_directories(${CMAKE_SOURCE_DIR}/libs/eigen)
include_directories(${CMAKE_SOURCE_DIR}/libs/gnuplot-iostream)

# find_package(Boost REQUIRED COMPONENTS
#     iostreams system filesystem
# )

# # find dependencies (Boost)
# find_package(Boost REQUIRED COMPONENTS 
#             iostreams system filesystem)
#   # adds the search path for include


# LIBRARIES 
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

add_library(Compute
  src/compute.cpp
)

# add_library(PlotHist 
#   src/plot_histogram.cpp
# )


# GNUPLOT EXAMPLE

# add_executable(example_histogram tests/example_histogram.cpp)
#   # adds linked libraries to produce executable
# target_link_libraries(example_histogram PUBLIC Image Pixel Reader PlotHist gtest_main gtest pthread PRIVATE
#                       Boost::iostreams
#                       Boost::system
##                      Boost::filesystem)


add_executable(example_compute tests/test_compute.cpp)
target_link_libraries(example_compute PUBLIC Reader Image Pixel Compute gtest_main gtest pthread)

add_executable(test_image tests/test_image.cpp)
target_link_libraries(test_image Image Pixel gtest_main gtest pthread)

add_executable(test_pixel tests/test_pixels.cpp)
target_link_libraries(test_pixel Pixel gtest_main gtest pthread)

add_executable(test_IO tests/test_IO.cpp)
target_link_libraries(test_IO Pixel Image Reader Writer gtest_main gtest pthread)

add_executable(test_transform tests/test_transform.cpp)
target_link_libraries(test_transform Image Pixel Reader Writer Transform gtest_main gtest pthread)

add_executable(test_Filter tests/test_Filter.cpp)
target_link_libraries(test_Filter Image Pixel Reader Writer Transform)

# # PROGRAM EXECUTABLE
# add_executable(image_processor src/image_processor.cpp)
# target_link_libraries(image_processor PUBLIC 
#                                         Transform 
#                                         Compute 
#                                         Reader 
#                                         Image 
#                                         Pixel 
#                                         PlotHist 
#                                         Writer 
#                                       PRIVATE
#                                         Boost::iostreams
#                                         Boost::system
#                                         Boost::filesystem)

# #add_custom_target(test ./test_image DEPENDS test_pixel)
