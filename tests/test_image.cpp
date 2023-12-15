#include<iostream>
#include "../src/Image.hh"
#include "../src/MyExceptions.hh"
#include<gtest/gtest.h>

using namespace std;

// Fixture class
class ImageTest : public ::testing::Test {
    protected:
    void SetUp() override{

        Pixel p00_({0,1,2});
        Pixel p01_({1,2,3});
        Pixel p10_({2,3,4});
        Pixel p11_({3,4,5});

        p00 = p00_;
        p01 = p01_;
        p10 = p10_;
        p11 = p11_;
    }

    Pixel p00 ={0};
    Pixel p01 ={0};
    Pixel p10 ={0};
    Pixel p11 ={0};
};

TEST_F(ImageTest,constructors_get_set_fcts){

    vector<vector<Pixel>> vec_pix_0({{p00,p01},{p10,p11}});
    Image img0(vec_pix_0);

    // Test constructor
    EXPECT_EQ(img0.get_pixel(0,0).get_pixel_data(),p00.get_pixel_data()) << "Image img0 pixel (0,0) is not (0,1,2) as expected : pb in the Image constructor";
    
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


TEST_F(ImageTest,conversions_image_matrices){
    vector<vector<Pixel>> vec_pix_0({{p00,p01},{p10,p11}});
    Image img0(vec_pix_0);
    
    MatrixXcd band1({{0,1},{2,3}});
    MatrixXcd band2({{1,2},{3,4}});
    MatrixXcd band3({{2,3},{4,5}});

    vector<MatrixXcd> expect_bands({band1,band2,band3});
    /// Test conversion Image to matrices of bands
    EXPECT_EQ(img0.bands_as_complex_matrices(),expect_bands) << "Bands extracted from Image object are not equal to the expected ones";
    
    /// Test conversion between matrices of the bands (<vector<MatrixXcd>>) and Images (<vector<vector<Pixel>>)
    // Is this function the inverse of the previous one?
    Image img1(expect_bands);
    for(int i(0);i<img0.shape()[0];++i){
        for(int j(0);j<img0.shape()[1];++j){
            EXPECT_EQ(img0.get_pixel(i,j).get_pixel_data(),img1.get_pixel(i,j).get_pixel_data()) << "Deconversion matrices of channels to 2D vector of Pixels is wrong on Pixel (" << i << "," << j << ")";
        }
    }
    // Are the negative values correctly handled?
    MatrixXcd dummy_band({{0,-1.5},{-10,-3.4}});
    vector<MatrixXcd> band({dummy_band});
    Image img2(bands_matrix_to_2D_pixel_vector(band));
    Pixel pix_null({0});

    for(int i(0);i<2;++i){
        for(int j(0);j<2;++j){
            EXPECT_EQ(pix_null.get_pixel_data(),img2.get_pixel(i,j).get_pixel_data()) << "Function bands_matrix_to_2D_pixel_vector failed to handle negative values in bands input";
        }
    }
}

