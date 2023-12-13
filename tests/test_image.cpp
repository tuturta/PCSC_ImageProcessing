#include<iostream>
#include "../src/Image.hh"
#include "../src/MyExceptions.hh"
#include<gtest/gtest.h>

using namespace std;

TEST(test_image,constructors_and_fcts){

    vector<unsigned int> p00_val({0,1,2});
    vector<unsigned int> p01_val({1,2,3});
    vector<unsigned int> p10_val({2,3,4});
    vector<unsigned int> p11_val({4,5,6});

    Pixel p00(p00_val);
    Pixel p01(p01_val);
    Pixel p10(p10_val);
    Pixel p11(p11_val);

    vector<vector<Pixel>> vec_pix_0({{p00,p01},{p10,p00}});
    
    Image img0(vec_pix_0);

    // Test constructor
    EXPECT_EQ(img0.get_pixel(0,0).get_pixel_data(),p00_val) << "Image img0 pixel (0,0) is not (0,1,2) as expected : pb in the Image constructor";
    
    // Test exceptions in get_pixel method 
    ASSERT_THROW(img0.get_pixel(img0.shape()[0]+2,0),InvalidDimException) << "get_pixel(row_idx,col_idx) does not throw an invalid dimension error when called with invalid row_idx";
    ASSERT_THROW(img0.get_pixel(0,img0.shape()[1]+2),InvalidDimException) << "get_pixel(row_idx,col_idx) does not throw an invalid dimension error when called with invalid col_idx";

    // Test shape method
    array<size_t,2> shape_expected({2,2});
    EXPECT_EQ(img0.shape(),shape_expected) << "Method shape does not output the expected shape";
    
    //test copy constructor
    Image img0_copy(img0);
    for(int i(0);i<img0.shape()[0];++i){
        for(int j(0);j<img0.shape()[1];++j){
            EXPECT_EQ(img0.get_pixel(i,j).get_pixel_data(),img0_copy.get_pixel(i,j).get_pixel_data()) << "Copy of img0 differs from img0 on pixel (" << i << "," << j << ")";
        }
    }
    // Test row/columns management (set/get)
    vector<Pixel> new_first_row({p11,p00});
    img0.set_row(new_first_row,0);
    for(int j(0);j<img0.shape()[1];++j){
        EXPECT_EQ(img0.get_pixel(0,j).get_pixel_data(),new_first_row[j].get_pixel_data()) << "Pixel (0," << j << ") after setting new row is not new_first_row[" << j <<"]...";
    }

    vector<Pixel> new_first_col({p10,p01});
    img0.set_column(new_first_col,0);
    for(int i(0);i<img0.shape()[0];++i){
        EXPECT_EQ(img0.get_pixel(i,0).get_pixel_data(),new_first_col[i].get_pixel_data()) << "Pixel (" << i << ",0) after setting new column is not new_first_col[" << i <<"]...";
    }
    
    ASSERT_THROW(img0.get_row(img0.shape()[0]+2),InvalidDimException) << "get_row(row_idx) does not throw an invalid dimension error when called with invalid row_idx";
    ASSERT_THROW(img0.get_column(img0.shape()[1]+2),InvalidDimException) << "get_column(col_idx) does not throw an invalid dimension error when called with invalid col_idx";
}