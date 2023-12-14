#pragma once
#include "Pixel.hh"
#include<vector>
#include<array>
#include "MyExceptions.hh"

// Class image
class Image{
    // Constructors
    public: 
        Image(std::vector<std::vector<Pixel>> const& data,unsigned int max=255):data(data), max(max){
            /// Check the number of channels
            size_t dim_ref(data[0][0].dim());
            for(size_t i(0);i<data.size();++i){
                for(size_t j(0); j<data[0].size();++j){
                    if(data[i][j].dim()!=dim_ref){
                        throw InvalidDimException("Pixel dimensions are not consistent with each other, I can't build an image from this pixel collection");
                    }
                }
            }
            bands_number = dim_ref;
        }
        Image(Image const& img):data(img.get_data()),max(img.get_max()){} // copy constructor
    // operators :
        friend std::ostream & operator << (std::ostream &out, const Image &img); 

    // Attributes
    private:
        std::vector<std::vector<Pixel>> data;
        size_t bands_number;
        unsigned int max;
    // Methods 
    public : 
        std::array<size_t,2> shape() const;
        size_t Nbands() const;
        unsigned int get_max() const;
        std::vector<std::vector<Pixel>> get_data() const;
        // access pixel
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
        // access rows/columns
        void set_row(std::vector<Pixel> const& pix_row,unsigned int i);
        std::vector<Pixel> get_row(unsigned int i) const;
        void set_column(std::vector<Pixel> const& pix_col,unsigned int j);
        std::vector<Pixel> get_column(unsigned int j) const;
        std::vector<unsigned int> get_band_1D(unsigned int b) const;
};  