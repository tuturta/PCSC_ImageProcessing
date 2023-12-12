#pragma once
#include "Pixel.hh"
#include<vector>
#include<array>

using namespace std;

// Class image
class Image{
    // Constructors
    public: 
        Image(vector<vector<Pixel>> const& data):data(data){}
        Image(Image const& img):data(img.data){} // copy constructor
    // operators :
        friend ostream & operator << (ostream &out, const Image &img); 

    // Attributes
    private:
        vector<vector<Pixel>> data;  
    // Methods 
    public : 
        array<size_t,2> shape() const;
        // access pixel
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
        // access rows/columns
        void set_row(vector<Pixel> const& pix_row,unsigned int i);
        vector<Pixel> get_row(unsigned int i) const;
        void set_column(vector<Pixel> const& pix_col,unsigned int j);
        vector<Pixel> get_column(unsigned int j) const;
};  