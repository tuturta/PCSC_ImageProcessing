#include "Pixel.hh"
#include "MyExceptions.hh"

// Definitions of the methods:

size_t Pixel::dim() const{
    // Returns the dimension of the pixel
    return values.size();
}

void Pixel::set_channel_value(size_t channel_id, unsigned int value){ 
    // Set the channel 'channel_id' to the value 'value'
    if (channel_id > dim()){
        std::string error_message="Cannot set channel "+std::__cxx11::to_string(channel_id)+" since pixel has "+std::__cxx11::to_string(dim())+" channels";
        throw InvalidDimException(error_message);
    } else {
        values[channel_id]=value;
    }
}

unsigned int Pixel::get_channel_value(size_t channel_id) const{
    // Returns the value stored in channel number 'channel_id'
    if (channel_id > dim()){
        std::string error_message="Cannot get channel "+std::__cxx11::to_string(channel_id)+" since pixel has "+std::__cxx11::to_string(dim())+" channels";
        throw InvalidDimException(error_message);
    } else {
        return values[channel_id];
    }
}

std::vector<unsigned int> Pixel::get_pixel_data() const{
    return values;
}

// Assignment operator 
Pixel& Pixel::operator=(const Pixel& P){
    values=P.values;
    return *this;
};

// << operator
std::ostream & operator<<(std::ostream &out,Pixel const& P){
    for(size_t i(0);i<P.dim();++i){
        out << P.get_channel_value(i) << ' ';
    }
    return out;
}
