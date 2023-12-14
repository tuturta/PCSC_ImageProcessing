#include<iostream>
#include "Image.hh"
#include "MyExceptions.hh"
#include<string>

using namespace std;

// Definitions of the methods
array<size_t,2> Image::shape() const{
    array<size_t,2> shape({data.size(),data[0].size()});
    return shape;
}

size_t Image::Nbands() const{
    return bands_number;
}

unsigned int Image::get_max() const{
    return max;
}

vector<vector<Pixel>> Image::get_data() const{
    return data;
}

void Image::set_pixel(Pixel const& P, unsigned int i, unsigned int j){
    array<size_t,2> dims(shape());
    if(i>dims[0] | j>dims[1]){
        string error_message="Cannot set pixel ("+to_string(i)+","+to_string(j)+") since image has shape ("+to_string(dims[0])+","+to_string(dims[1])+")";
        throw InvalidDimException(error_message);
    } else{
        data[i][j] = P;
    }
}

Pixel Image::get_pixel(unsigned int i, unsigned int j) const{
    array<size_t,2> dims(shape());
    if(i>dims[0] | j>dims[1]){
        string error_message="Cannot get pixel ("+to_string(i)+","+to_string(j)+") since image has shape ("+to_string(dims[0])+","+to_string(dims[1])+")";
        throw InvalidDimException(error_message);
    } else{
        return data[i][j];
    }
}

void Image::set_row(vector<Pixel> const& pix_row,unsigned int i){ 
    array<size_t,2> dims(shape());
    if(i>dims[0] | pix_row.size()!=dims[1]){
        string error_message="Cannot set row "+to_string(i)+" since image has "+to_string(dims[0])+" rows";
        throw InvalidDimException(error_message);
    } else {
        for(size_t j(0);j<dims[1];++j){
            set_pixel(pix_row[j],i,j);
        }
    }
}

void Image::set_column(vector<Pixel> const& pix_col,unsigned int j){
    array<size_t,2> dims(shape());
    if(j>dims[1] | pix_col.size()!=dims[0]){
        string error_message="Cannot set column "+to_string(j)+" since image has "+to_string(dims[1])+" columns";
        throw InvalidDimException(error_message);
    } else {
        for(size_t i(0);i<dims[0];++i){
            set_pixel(pix_col[i],i,j);
        }
    }
}

vector<Pixel> Image::get_row(unsigned int i) const{
    array<size_t,2> dims(shape());
    if(i>dims[0]){
        string error_message="Cannot get row "+to_string(i)+" since image has "+to_string(dims[0])+" rows";
        throw InvalidDimException(error_message);
    }else{
        return data[i];
    }
}

vector<Pixel> Image::get_column(unsigned int j) const{
    array<size_t,2> dims(shape());
    if(j>dims[1]){
        string error_message="Cannot set column "+to_string(j)+" since image has "+to_string(dims[1])+" columns";
        throw InvalidDimException(error_message);
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

/**
 * @brief This method returns a band of the image as a list. The only argument is the band index.
 * 
 * @param b 
 * @return vector<unsigned int> 
 */
vector<unsigned int> Image::get_band_1D(unsigned int b) const{
    if(b>bands_number){
        string error_message="Cannot get band "+to_string(b)+" since image has "+to_string(bands_number)+" bands";
        throw InvalidDimException(error_message);
    } else {
        array<size_t,2> dims(shape());
        vector<unsigned int> band_1D(dims[0]*dims[1],0);
        for(size_t i(0);i<dims[0];++i){
            for(size_t j(0);j<dims[1];++j){
                band_1D[i*dims[1]+j]= get_pixel(i,j).get_channel_value(b);
            }
        }
        return band_1D;
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