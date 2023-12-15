#include<iostream>
#include "Image.hh"
#include "MyExceptions.hh"
#include<string>

using namespace std;

Image::Image(std::vector<std::vector<Pixel>> const& data,unsigned int max):data(data), max(max){
            // Check the number of channels
            size_t dim_ref(data[0][0].dim());
            for(size_t i(0);i<data.size();++i){
                for(size_t j(0); j<data[0].size();++j){
                    if(data[i][j].dim()!=dim_ref){
                        throw InvalidDimException("Pixel dimensions are not consistent with each other, I can't build an image from this pixel collection");
                    }
                }
            }
            bands_number = dim_ref;
        }

Image::Image(Image const& img):data(img.get_data()),max(img.get_max()){}

Image::Image(vector<MatrixXcd> const& bands_matrices,unsigned int max) : data(bands_matrix_to_2D_pixel_vector(bands_matrices)),max(max){}

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

std::vector<MatrixXcd> Image::bands_as_complex_matrices() const{
    array<size_t,2> img_dims(shape());
    MatrixXcd matrix(img_dims[0],img_dims[1]);
    std::vector<MatrixXcd> bands_matrices(bands_number,matrix);
    
    for (size_t i(0);i<img_dims[0];++i){
        for(size_t j(0);j<img_dims[1];++j){
            for(size_t b(0); b<bands_number; ++b){
                bands_matrices[b](i,j)=data[i][j].get_channel_value(b);
            }
        }
    }
    return bands_matrices;
}

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



// Function related to Image manipulation
std::vector<std::vector<Pixel>> bands_matrix_to_2D_pixel_vector(std::vector<MatrixXcd> const& bands_matrices){
    // CHECK DIMENSIONS (TODO)

    // Get dimensions of the problem 
    unsigned int num_bands(bands_matrices.size());
    size_t m(bands_matrices[0].rows());
    size_t n(bands_matrices[0].cols());

    // Allocate space for future img_data to fill
    vector<unsigned int> null_pix_data(num_bands,0);
    Pixel null_pix(null_pix_data);
    std::vector<Pixel> null_row(m,null_pix);
    std::vector<std::vector<Pixel>> img_data(n,null_row);

    // Fill the img_data, rounding values to get unsigned int, else set 0 (OR throwing error if negative values encoutered?)
    for(size_t i(0);i<m;++i){
        for(size_t j(0);j<n;++j){
            for(size_t b(0);b<num_bands;++b){
                double value(bands_matrices[b](i,j).real());
                if(value>=0){
                    img_data[i][j].set_channel_value(b,round(value));
                } else {
                    img_data[i][j].set_channel_value(b,0); 
                    //throw NegativeException("Tried to set a negative value as channel value");
                }
            }
        }
    }
    return img_data;
}
