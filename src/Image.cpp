#include<iostream>
#include "Image.hh"

using namespace std;


// Definitions of the methods
void Image::set_pixel(Pixel const& P, unsigned int i, unsigned int j){
    data[i][j] = P;
}

Pixel Image::get_pixel(unsigned int i, unsigned int j) const{
    return data[i][j];
}

array<size_t,2> Image::shape() const{
    // TODO : handle the case of an empty image or not 2D : is it possible? 
    array<size_t,2> shape({data.size(),data[0].size()});
    return shape;
}

// << operator
ostream & operator<<(ostream &out,Image const& img){
    array<size_t,2> dims(img.shape());
    
    for(size_t i(0);i<dims[0];++i){
        for(size_t j(0);j<dims[1];++j){
        out << img.data[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}