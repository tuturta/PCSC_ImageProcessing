#include<iostream>
#include "src/Image.hh"

using namespace std;

int main(){
    // declare 4 pixels 
    Pixel p1({0,0,0});
    Pixel p2({1,1,1});
    Pixel p3({2,2,2});
    Pixel p4({3,3,3});
    
    // make a 2D array of pixels
    vector<vector<Pixel>> data{{p1,p2},{p3,p4}};
    
    // Build an image with this 2D array :
    Image img(data);
    
    // Access pixel 0,0
    cout << "On loc 0,0, channels values are " << img.get_pixel(0,0) << endl;
    
    // Change the channel values of that pixel
    img.set_pixel(p2,0,0);

    // Access this pixel and print it
    cout << "On loc 0,0, new channels values are " << img.get_pixel(0,0) << endl;

    // cout the image :
    cout << "Our image is thus : " << endl << img << endl;
    
    return 0;
}
