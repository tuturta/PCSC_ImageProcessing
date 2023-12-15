#include "../src/plot_histogram.cpp"
#include "../src/Image.hh"
#include<gtest/gtest.h>
#include "../src/reader.hh"

int main(){
    PPMReader ppm_reader("../in/test_photo.ppm");
    Image image(ppm_reader.read());
    string output_path("../output/histogram_test_photo");
    unsigned int Nbins(256);

    draw_histogram(image,output_path,Nbins);

    return 0;
}