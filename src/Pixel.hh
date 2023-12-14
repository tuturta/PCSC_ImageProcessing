#pragma once

#include<vector>
#include<iostream>

// Class Pixel : a pixel is a collection of N positive integers (e.g. N=1 for grayscale pixel, N=3 for RGB pixel,...)
class Pixel{
    // Constructors
    public :
        Pixel(std::initializer_list<unsigned int> const& val): values(val){}
        Pixel(std::vector<unsigned int> channels): values(channels){}
        Pixel (Pixel const&P):values(P.values){} // constructeur de copie
        
    // Operators :
        Pixel& operator=(const Pixel& P);
        friend std::ostream & operator << (std::ostream &out, const Pixel &c);    // Methods 
    public : 
        size_t dim() const;
        unsigned int get_channel_value(size_t channel_id) const;
        void set_channel_value(size_t channel_id, unsigned int value);
        std::vector<unsigned int> get_pixel_data() const;

    // Attributes 
    private :
        std::vector<unsigned int> values;
};
