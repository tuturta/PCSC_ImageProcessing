#include "../src/histogram.cpp"
#include "../src/Image.hh"
#include<gtest/gtest.h>
#include "../src/reader.hh"

int main(){
    TXTReader txt_reader("../in/test.txt");
    Image image1(txt_reader.read());

    string output_path1("../output/histogram_txtimg");
    unsigned int Nbins1(10);
    draw_histogram(image1,output_path1,Nbins1);

    PPMReader ppm_reader("../in/test.ppm");
    Image image2(ppm_reader.read());

    string output_path2("../output/histogram_ppmimg");
    unsigned int Nbins2(20);
    draw_histogram(image2,output_path2,Nbins2);
    
    return 0;
}