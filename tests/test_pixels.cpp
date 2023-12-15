#include<iostream>
#include "../src/Pixel.hh"
#include <gtest/gtest.h>
#include "../src/MyExceptions.hh"

using namespace std;

TEST(PixelTest,construction_and_getset_functions){
    // Test initializer list based constructor :
    Pixel p0({0,0,0,});
    Pixel p1({0,30,2});
    vector<unsigned int> p0val({0,0,0});
    vector<unsigned int> p1val({0,30,2});

    EXPECT_EQ(p0val,p0.get_pixel_data()) << "Pixel (0,0,0) values are not (0,0,0) : problem in the constructor taking intitializer list";
    EXPECT_EQ(p1val,p1.get_pixel_data()) << "Pixel (0,32,2) values are not (0,0,0) : problem in the constructor taking intitializer list";
    
    // Test vector<unsigned int> based constructor :
    Pixel p0_vec(p0val);
    EXPECT_EQ(p0val,p0_vec.get_pixel_data()) << "Pixel (0,0,0) values are not (0,0,0) : problem in the constructor taking vector<unsigned int> as argument";
    
    // Test copy constructor
    Pixel p0_(p0);
    EXPECT_EQ(p0_.get_pixel_data(),p0.get_pixel_data()) << "Copy constructor has built a different pixel than the one to copy";

    // Test set/get functions and their exception management
    ASSERT_THROW(p0.get_channel_value(5),InvalidDimException) << "get_channel_value(channel_idx) does not throw an invalid dimension error when called with invalid channel_idx";
    ASSERT_THROW(p0.set_channel_value(5,0),InvalidDimException) << "set_channel_value(channel_idx,new_val) does not throw an invalid dimension error when called with invalid channel_idx";
    p0.set_channel_value(0,20);
    EXPECT_EQ(p0.get_channel_value(0),20) << "set_channel_value(channel_idx,new_val) does not did not set new_value on channel channel_idx";
    
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}