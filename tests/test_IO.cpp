#include "../src/reader.hh"
#include "../src/writer.hh"
#include "../src/Image.hh"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include<gtest/gtest.h>

using namespace std;

class ReaderTxtTest : public ::testing::Test {
    protected:
    void SetUp() override{
            // Create a file at path path
            ofstream file(path);
    }
    void TearDown() override{
            // Clear content of the file
            ofstream ofs;
            ofs.open(path, ofstream::out | ofstream::trunc);
            ofs.close();
    }
    const string path = "in/Gtest.txt";
};

/*=== TEST OF CLASS TXTReader ===*/
TEST_F(ReaderTxtTest, read_unknown_path){

    const string path1 = "in/inexisting_file.txt";
    remove("in/inexisting_file.txt"); // remove the file if existing
    TXTReader txt(path1); 
    ASSERT_THROW(txt.read(), ifstream::failure) << "The path should not exist!"; 
}

TEST_F(ReaderTxtTest, unmatching_dimension1){
    // Create a file at path path
    ofstream file(path);

    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2 " << "1 " << '\n';
    // Enter the values of each pixels
    file << "1 " << "1";
    file.close();

    // Here the real dimension 2x1x1 does not match with enter dimension
    TXTReader txt(path); 

    ASSERT_THROW(txt.read(), InvalidDimException) << "Unmatching real and enter dimension. An Exception should have been raised!"; 
}

TEST_F(ReaderTxtTest, unmatching_dimension2){
    // Create a file at path path
    ofstream file(path);
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2 " << "2 " << '\n';
    // Enter the values of each pixels
    file << "1 " << "1 " << "1 " << '\n';
    file.close();

    TXTReader txt(path); 
    ASSERT_THROW(txt.read(), InvalidDimException) << "Unmatching real and enter dimension. An Exception should have been raised!";
}

TEST_F(ReaderTxtTest, negative_dimension){
    // Create a file at path path
    ofstream file(path);
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "-2 " << "2 " << '\n';
    // Enter the values of each pixels
    file << "1 " << "1 " << "   1 " << "1 " << '\n';
    file << "1 " << "1 " << "   1 " << "1 " << '\n';
    file.close();

    TXTReader txt(path); 
    ASSERT_THROW(txt.read(), NegativeDimException) << "Dimension cannot be negative, an exception should have been raised !"; 
}

TEST_F(ReaderTxtTest, negative_input_value){
    // Create a file at path path
    ofstream file(path);
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2 " << "2 " << '\n';
    // Enter the values of each pixels
    file << "1 " << "-1 " << "   1 " << "1 " << '\n';
    file << "1 " << "1 " << "   1 " << "1 " << '\n';
    file.close();

    TXTReader txt(path); 
    ASSERT_THROW(txt.read(), NegativePixelValueException) << "A pixel cannot have a negative value, an exception should have been raised !"; 
}

TEST_F(ReaderTxtTest, read_correct_input){
    // Create a file at path path
    ofstream file(path);
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2 " << "2 " << '\n';
    // Enter the values of each pixels
    file << "1 " << "10 " << "   2 " << "20 " << '\n';
    file << "3 " << "30 " << "   4 " << "40 " << '\n';
    file.close();

    // Test if the file has been correctly read
    TXTReader txt(path); 
    Image image(txt.read());
    vector<Pixel> row;
    size_t count(1);
    for(size_t i(0); i < image.shape()[0]; ++i){
        row = image.get_row(i);
        for(const auto& pixel: row){
            EXPECT_EQ(pixel.get_channel_value(0), count) << "Pixel 0 at row " + to_string(i) + " is not correct.";
            EXPECT_EQ(pixel.get_channel_value(1), count*10)<< "Pixel 1 at row " + to_string(i) + " is not correct.";
            count += 1;
        }
    }
}

/*=== TEST OF CLASS PPMReader ===*/
class ReaderPpmTest : public ReaderTxtTest {
    protected:
    const string path = "in/Gtest.ppm";
    
};

TEST_F(ReaderPpmTest, read_unknown_path){

    const string path1 = "in/inexisting_file.ppm";
    remove("in/inexisting_file.ppm"); // remove the file if existing
    PPMReader txt(path1); 
    ASSERT_THROW(txt.read(), ifstream::failure) << "The path should not exist!"; 
}

TEST_F(ReaderPpmTest, unmatching_dimension1){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P3\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2" << '\n';
    // Specify the max value 
    file << "255\n";

    // Enter the values of each pixels
    file << "1 " << "1";
    file.close();

    // Here the real dimension 2x1x1 does not match with enter dimension
    PPMReader txt(path); 

    ASSERT_THROW(txt.read(), InvalidDimException) << "Unmatching real and enter dimension. An Exception should have been raised!"; 
}

TEST_F(ReaderPpmTest, unmatching_dimension2){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P3\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2" << '\n';
    // Specify the max value 
    file << "255\n";

    // Enter the values of each pixels
    file << "1 " << "1 " << "1 " << '\n';
    file.close();

    PPMReader txt(path); 
    ASSERT_THROW(txt.read(), InvalidDimException) << "Unmatching real and enter dimension. An Exception should have been raised!";
}

TEST_F(ReaderPpmTest, negative_dimension){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P3\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "-2 " << '\n';
    // Specify the max value 
    file << "255\n";

    // Enter the values of each pixels
    file << "1 " << "1 " << "   1 " << "1 " << '\n';
    file << "1 " << "1 " << "   1 " << "1 " << '\n';
    file.close();

    PPMReader txt(path); 
    ASSERT_THROW(txt.read(), NegativeDimException) << "Dimension cannot be negative, an exception should have been raised !"; 
}

TEST_F(ReaderPpmTest, negative_input_value){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P3\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2"<< '\n';
    // Specify the max value 
    file << "255\n";

    // Enter the values of each pixels
    file << "1 " << "-1 " << " 1 " << "1 " << " 1 " << "1" << '\n';
    file << "1 " << "1 " << " 1 " << "1 " << " 1 " << "1" << '\n';
    file.close();

    PPMReader txt(path); 
    ASSERT_THROW(txt.read(), NegativePixelValueException) << "A pixel cannot have a negative value, an exception should have been raised !"; 
}

TEST_F(ReaderPpmTest, wrong_ppm_format){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P5\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2"<< '\n';
    // Specify the max value 
    file << "255\n";
    
    // Enter the values of each pixels
    file << "1 " << "1 " << " 1 " << "1 " << " 1 " << "1" << '\n';
    file << "1 " << "1 " << " 1 " << "1 " << " 1 " << "1" << '\n';
    file.close();

    PPMReader txt(path); 
    ASSERT_THROW(txt.read(), WrongPpmFormatException); 
}

TEST_F(ReaderPpmTest, read_correct_input){
    // Create a file at path path
    ofstream file(path);
    // Specify the format
    file << "P3\n";
    // Specifiy the dimension : nb_cols, nb_rows, nb_channels
    file << "2 " << "2 " << '\n';
    // Specify the max value 
    file << "400\n";

    // Enter the values of each pixels
    file << "1 " << "10 " << "100 " << "2 " << "20 " << "200\n";
    file << "3 " << "30 " << "300 " << "4 " << "40 " << "400\n";
    file.close();

    // Test if the file has been correctly read
    PPMReader txt(path); 
    Image image(txt.read());
    vector<Pixel> row;
    size_t count(1);
    for(size_t i(0); i < image.shape()[0]; ++i){
        row = image.get_row(i);
        for(const auto& pixel: row){
            EXPECT_EQ(pixel.get_channel_value(0), count) << "Pixel 0 at row " + to_string(i) + " is not correct.";
            EXPECT_EQ(pixel.get_channel_value(1), count*10)<< "Pixel 1 at row " + to_string(i) + " is not correct.";
            EXPECT_EQ(pixel.get_channel_value(2), count*100)<< "Pixel 2 at row " + to_string(i) + " is not correct.";
            count += 1;
        }
    }
}

/* === Test of Classes Writer*/

class WriterTestTxt : public ::testing::Test {
    protected: 
        void SetUp() override{
            ofstream ofs;
            ofs.open(path, ofstream::out | ofstream::trunc);
            ofs.close();
        }
        
        const Image image = vector<vector<Pixel>>
        ({
            {Pixel({1,2,3}), Pixel({4,5,6})},
            {Pixel({10,11,12}), Pixel({13,14,15})}
        });
        const string path = "in/Gtest.txt";
};

TEST_F(WriterTestTxt, correct_extension_txt){
    // Test if the extension is correct
    ASSERT_THROW(TXTWriter txt_wrong("in/Gtest", image), WrongFileFormatException);
}

TEST_F(WriterTestTxt, correct_writing_txt){
    // Write the image in the file
    TXTWriter txt_out(path, image);
    txt_out.write();
    // Read the image
    TXTReader txt_in(path);
    Image image_written(txt_in.read());

    // Compare with the original image
    size_t nb_rows(image.shape()[0]);
    size_t nb_cols(image.shape()[1]);
    size_t nb_channels(image.get_pixel(0,0).dim());
    
    for(size_t i(0); i<nb_rows; ++i){
        for(size_t j(0); j<nb_cols; ++j){
            for(size_t k(0); k<nb_channels; ++k){
                EXPECT_EQ(image_written.get_pixel(i,j).get_channel_value(k),image.get_pixel(i,j).get_channel_value(k)) << "Image written is not the same than the original image";
            }
        }
    }        

}


class WriterTestPpm : public WriterTestTxt {
    protected:
        const string path = "in/Gtest.ppm";
};

TEST_F(WriterTestPpm, correct_extension_txt){
    // Test if the extension is correct
    ASSERT_THROW(PPMWriter ppm_wrong("in/Gtest", image), WrongFileFormatException);
}

TEST_F(WriterTestPpm, correct_writing_txt){
    // Write the image in the file
    PPMWriter ppm_out(path, image);
    ppm_out.write();
    // Read the image
    PPMReader ppm_in(path);
    Image image_written(ppm_in.read());

    // Compare with the original image
    size_t nb_rows(image.shape()[0]);
    size_t nb_cols(image.shape()[1]);
    size_t nb_channels(image.get_pixel(0,0).dim());
    
    for(size_t i(0); i<nb_rows; ++i){
        for(size_t j(0); j<nb_cols; ++j){
            for(size_t k(0); k<nb_channels; ++k){
                EXPECT_EQ(image_written.get_pixel(i,j).get_channel_value(k),image.get_pixel(i,j).get_channel_value(k)) << "Image written is not the same than the original image";
            }
        }
    }        

}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}