#pragma once

#include<vector>
#include<iostream>

using namespace std;

// Class Pixel : a pixel is a collection of N positive integers (e.g. N=1 for grayscale pixel, N=3 for RGB pixel,...)
class Pixel{
    // Constructor
    public :
        Pixel(initializer_list<unsigned int> const& val){
            // A Pixel can be built from a list of N positive integers
		    for (auto i : val) { 
                values.push_back(i); 
            }
            cout << "Pixel created successfully" << endl;
        }
    // Methods 
    public : 
        size_t dim();
        void set_channel_value(size_t channel_id, unsigned int value);
        unsigned int get_channel_value(size_t channel_id);
    // Attributes 
    private :
        vector<unsigned int> values;
};
