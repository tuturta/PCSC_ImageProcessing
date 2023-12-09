#include<iostream>
#include "Image.hh"
#include "MyExceptions.hh"

using namespace std;

// Definitions of the methods
array<size_t,2> Image::shape() const{
    array<size_t,2> shape({data.size(),data[0].size()});
    return shape;
}

void Image::set_pixel(Pixel const& P, unsigned int i, unsigned int j){
    array<size_t,2> dims(shape());
    if(i>dims[0] | j>dims[1]){
        throw InvalidDimException();
    } else{
        data[i][j] = P;
    }
}

Pixel Image::get_pixel(unsigned int i, unsigned int j) const{
    array<size_t,2> dims(shape());
    if(i>dims[0] | j>dims[1]){
        throw InvalidDimException();
    } else{
        return data[i][j];
    }
}

void Image::set_row(vector<Pixel> const& pix_row,unsigned int i){ 
    array<size_t,2> dims(shape());
    if(i>dims[0] | pix_row.size()!=dims[1]){
        throw InvalidDimException();
    } else {
        for(size_t j(0);j<dims[1];++j){
            set_pixel(pix_row[j],i,j);
        }
    }
}

void Image::set_column(vector<Pixel> const& pix_col,unsigned int j){
    array<size_t,2> dims(shape());
    if(j>dims[1] | pix_col.size()!=dims[0]){
        throw InvalidDimException();
    } else {
        for(size_t i(0);i<dims[0];++i){
            set_pixel(pix_col[i],i,j);
        }
    }
}

vector<Pixel> Image::get_row(unsigned int i) const{
    array<size_t,2> dims(shape());
    if(i>dims[0]){
        throw InvalidDimException();
    }else{
        return data[i];
    }
}

vector<Pixel> Image::get_column(unsigned int j) const{
    array<size_t,2> dims(shape());
    if(j>dims[1]){
        throw InvalidDimException();
    }else{
        // Build a new vector of pixels...
        Pixel zero_pix({0}); // TODO ajouter constructeur de vecteur de pixels nul de taille choisie?
        vector<Pixel> column(dims[1],zero_pix);
        //...Fill it with the image column
        for(size_t i(0);i<dims[1];++i){
            column[i]=data[i][j];
        }
        return column;
    }
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