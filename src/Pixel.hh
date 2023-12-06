#pragma once

#include<vector>
#include<iostream>

using namespace std;

// Class Pixel : a pixel is a collection of N positive integers (e.g. N=1 for grayscale pixel, N=3 for RGB pixel,...)
class Pixel{
    // Constructors
    public :
        Pixel(initializer_list<unsigned int> const& val): values(val){}
        Pixel(vector<unsigned int> channels): values(channels){}
        Pixel (Pixel const&P):values(P.values){} // constructeur de copie
        
    // Operators :
        Pixel& operator=(const Pixel& P);
        friend ostream & operator << (ostream &out, const Pixel &c);    // Methods 
    public : 
        size_t dim();
        //void set_pixel_data(unsigned int new_data[3]);
        unsigned int get_channel_value(size_t channel_id) const;
        void set_channel_value(size_t channel_id, unsigned int value);
    // Attributes 
    private :
        vector<unsigned int> values;
};
