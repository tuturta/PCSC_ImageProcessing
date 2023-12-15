#pragma once

#include<vector>
#include<iostream>

/// @brief A pixel is a collection of N positive integers (e.g. N=1 for grayscale pixel, N=3 for RGB pixel,...)
class Pixel{
    public :
        /// @brief Constructor from initializer list 
        /// @param val list of the future pixel's channel values (positive integers)
        Pixel(std::initializer_list<unsigned int> const& val): values(val){}
        
        /// @brief Constructor of Pixel from vector of unsigned int
        /// @param channels vector of unsigned int containing channel values for the Pixel
        Pixel(std::vector<unsigned int> channels): values(channels){}
        
        /// @brief Copy constructor
        /// @param P Pixel to copy
        Pixel (Pixel const&P):values(P.values){}
        
        /// @brief Assignment operator between Pixels
        /// @param P Picel to be assigned to
        /// @return Reference to a Pixel
        Pixel& operator=(const Pixel& P);

        /// @brief Operator <<, to write/display Pixels
        /// @param out std::ostream variable
        /// @param c Pixel to write
        /// @return 
        friend std::ostream & operator << (std::ostream &out, const Pixel &c);    // Methods 
    public : 
        /// @brief Provides the dimension of the Pixel (its number of channels)
        /// @return (size_t) number of channels
        size_t dim() const;
        
        /// @brief Accessor to get a channel value from its index in a Pixel
        /// @param channel_id 
        /// @return channel value (positive integer)
        unsigned int get_channel_value(size_t channel_id) const;
        
        /// @brief Set a channel value in a Pixel
        /// @param channel_id index of the channel to modify
        /// @param value channel value to set
        void set_channel_value(size_t channel_id, unsigned int value);
        
        /// @brief Accessor to get all channels values of a Pixel 
        /// @return channel values as a vector of positive integers 
        std::vector<unsigned int> get_pixel_data() const;

    // Attributes 
    private :
        std::vector<unsigned int> values; /// The channel values of the Pixel
};
