#pragma once
#include "Pixel.hh"
#include<vector>
#include<array>
#include "MyExceptions.hh"
#include<../eigen/Eigen/Dense>

using Eigen::MatrixXcd;

// Class image
class Image{
    // Constructors
    public: 
        /// @brief Constructs an Image from a 2D array of Pixels 
        /// @param data 2D array of pixel
        /// @param max unsigned int corresponding the the maximal possible pixel value (255 by default)
        Image(std::vector<std::vector<Pixel>> const& data,unsigned int max=255);

        /// Copy constructor
        Image(Image const& img);

        /// @brief Construct an image from the matrices of its channels
        /// @param bands_matrices vector<MatrixXcd>> where the MatrixScd's have all the same
        Image(std::vector<MatrixXcd> const& bands_matrices,unsigned int max=255);

    // operators :
        friend std::ostream & operator << (std::ostream &out, const Image &img); 

    // Attributes
    private:
        std::vector<std::vector<Pixel>> data;
        size_t bands_number;
        unsigned int max;
    // Methods 
    public : 
        std::array<size_t,2> shape() const;
        size_t Nbands() const;
        
        // basic getters 
        unsigned int get_max() const;
        std::vector<std::vector<Pixel>> get_data() const;
        
        // Pixelwise accessors
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
        
        // Rows/columns accessors
        void set_row(std::vector<Pixel> const& pix_row,unsigned int i);
        std::vector<Pixel> get_row(unsigned int i) const;
        void set_column(std::vector<Pixel> const& pix_col,unsigned int j);
        std::vector<Pixel> get_column(unsigned int j) const;

        // Get channels of the image as lists or matrices
        std::vector<unsigned int> get_band_1D(unsigned int b) const;
        std::vector<MatrixXcd> bands_as_complex_matrices() const;

};  

// Function to convert a vector of MatrixXcd to a vector<vector<Pixel>>
std::vector<std::vector<Pixel>> bands_matrix_to_2D_pixel_vector(std::vector<MatrixXcd> const& bands_mat);

