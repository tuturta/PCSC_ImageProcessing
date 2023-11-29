#include "Pixel.hh"

// Definitions of the methods:

size_t Pixel::dim(){
    // Returns the dimension of the pixel
    return values.size();
}

void Pixel::set_channel_value(size_t channel_id, unsigned int value){ 
    // Set the channel 'channel_id' to the value 'value'
    values[channel_id]=value;
}

unsigned int Pixel::get_channel_value(size_t channel_id){
    // Returns the value stored in channel number 'channel_id'
    return values[channel_id];
}



