#include "../src/Image.hh"
#include "../src/reader.hh"
#include "../src/compute.hh"

int main(){
    TXTReader txt_reader("../in/test.txt");
    Image image1(txt_reader.read());

    Contour_extraction contour_extraction(image1);
    contour_extraction.compute();
    return 0;
}