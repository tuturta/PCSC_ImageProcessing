#include<iostream>
#include "Image.hh"

using namespace std;

// Definitions of the methods
array<size_t,2> Image::shape() const{
    // TODO : handle the case of an empty image or not 2D : is it possible? 
    array<size_t,2> shape({data.size(),data[0].size()});
    return shape;
}

void Image::set_pixel(Pixel const& P, unsigned int i, unsigned int j){
    data[i][j] = P;
}

Pixel Image::get_pixel(unsigned int i, unsigned int j) const{
    return data[i][j];
}

void Image::set_row(vector<Pixel> const& pix_row,unsigned int i){
    // check dimension of the input row : 
    array<size_t,2> dims(shape());

    if(pix_row.size()!=dims[1]){
        invalid_argument err("pix_row size");
        throw(err);
    } else if(i>dims[0]){
        invalid_argument err("i");
        throw(err);
    } else {
        for(size_t j(0);j<dims[1];++j){
            set_pixel(pix_row[j],i,j);
        }
    }
}

void Image::set_column(vector<Pixel> const& pix_col,unsigned int j){
    // check dimension of the input row : 
    array<size_t,2> dims(shape());
    if(pix_col.size()!=dims[0]){
        invalid_argument err("pix_col size");
        throw(err);
    } else if(j>dims[1]){
        invalid_argument err("j");
        throw(err);
    } else {
        for(size_t i(0);i<dims[0];++i){
            set_pixel(pix_col[i],i,j);
        }
    }
}

vector<Pixel> Image::get_row(unsigned int i) const{
    array<size_t,2> dims(shape());
    if(i>dims[0]){
        invalid_argument err("i");
        throw(err);
    }else{
        return data[i];
    }
}

vector<Pixel> Image::get_column(unsigned int j) const{
    array<size_t,2> dims(shape());
    if(j>dims[1]){
        invalid_argument err("j");
        throw(err);
    }else{
        
        Pixel zero_pix({0}); // TODO ajouter constructeur de vecteur de pixels nul de taille choisie?
        vector<Pixel> column(dims[1],zero_pix);
        
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