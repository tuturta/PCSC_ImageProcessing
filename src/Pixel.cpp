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

/* TODO : adapt for any number of channels 
void Pixel::set_pixel_data(unsigned int new_data[3]){ 
    // Set all 3 channels to the new values contained in the array new_data
    for(size_t i(0);i<3;++i){
        set_channel_value(i,new_data[i]);
    }
}
*/
unsigned int Pixel::get_channel_value(size_t channel_id) const{
    // Returns the value stored in channel number 'channel_id'
    return values[channel_id];
}

// Assignment operator 
Pixel& Pixel::operator=(const Pixel& P){
    values=P.values;
    return *this;
};

// << operator
ostream & operator<<(ostream &out,Pixel const& P){
    for(size_t i(0);i<P.values.size();++i){
        out << P.get_channel_value(i) << ' ';
    }
    return out;
}
