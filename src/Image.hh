#pragma once
#include "Pixel.hh"
#include<vector>
#include<array>
#include "MyExceptions.hh"

using namespace std;

// Class image
class Image{
    // Constructors
    public: 
        Image(vector<vector<Pixel>> const& data):data(data){
            size_t dim_ref(data[0][0].dim());
            for(size_t i(0);i<data.size();++i){
                for(size_t j(0); j<data[0].size();++j){
                    if(data[i][j].dim()!=dim_ref){
                        throw InvalidDimException();
                    }
                }
            }
            bands_number = dim_ref;
        }
        Image(Image const& img):data(img.data){} // copy constructor
    // operators :
        friend ostream & operator << (ostream &out, const Image &img); 

    // Attributes
    private:
        vector<vector<Pixel>> data;
        size_t bands_number;
    // Methods 
    public : 
        array<size_t,2> shape() const;
        size_t Nbands() const;
        // access pixel
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
        // access rows/columns
        void set_row(vector<Pixel> const& pix_row,unsigned int i);
        vector<Pixel> get_row(unsigned int i) const;
        void set_column(vector<Pixel> const& pix_col,unsigned int j);
        vector<Pixel> get_column(unsigned int j) const;
        vector<unsigned int> get_band_1D(unsigned int b) const;
};  