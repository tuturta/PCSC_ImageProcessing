#pragma once
#include "Pixel.hh"
#include <vector>
#include <array>
#include "MyExceptions.hh"
#include <../eigen/Eigen/Dense>

using Eigen::MatrixXcd;

/// @brief 2D collection of Pixels, with one or more channels.
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
        /// @param bands_matrices vector<MatrixXcd>> where the MatrixXcd's have all the same
        Image(std::vector<MatrixXcd> const& bands_matrices,unsigned int max=255);

    // operators :
        friend std::ostream & operator << (std::ostream &out, const Image &img); 

    // Attributes
    private:
        std::vector<std::vector<Pixel>> data; /// The image data is a 2D collection of Pixels
        /// Number of channels
        size_t bands_number;  
        /// Maximal (possible) pixel channel value, e.g 255.
        unsigned int max; 
    // Methods 
    public : 
        /// @brief Provides the shape of the Image (number of columns and number of rows)
        /// @return Returns a std::array<size_t,2> corresponding to (columns_number,rows_number)
        std::array<size_t,2> shape() const;
        
        /// @brief  Simple accessor for the number of channels 
        /// @return Returns a size_t variable, corresponding to the bands_number attribute.
        size_t Nbands() const;
        
        /// @brief Simple accessor for the maximum pixel channel value 
        /// @return unsigned int corresponding to the attribute 'max'.
        unsigned int get_max() const;
        
        /// @brief Simple accessor to the image data
        /// @return std::vector<std::vector<Pixel>> corresponding to the attribute 'data'
        std::vector<std::vector<Pixel>> get_data() const;
        
        /// @brief Set a Pixel in the Image at a specified location
        /// @param P Pixel to put in the Image
        /// @param i row index
        /// @param j column index 
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        
        /// @brief Access a Pixel in the Image at a specified location
        /// @param i row index
        /// @param j column index
        /// @return Returns the wanted Pixel
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
        
        /// @brief Set a row of Pixel in an Image based on its index
        /// @param pix_row The row of Pixel to put in the Image
        /// @param i The row index 
        void set_row(std::vector<Pixel> const& pix_row,unsigned int i);
        
        /// @brief Get a row of Pixel in an Image based on its index
        /// @param i Row index 
        /// @return The desired row of Pixel
        std::vector<Pixel> get_row(unsigned int i) const;
        
        /// @brief Set a column of Pixel in an Image based on its index
        /// @param pix_col The column of Pixel to put in the Image
        /// @param j The column index
        void set_column(std::vector<Pixel> const& pix_col,unsigned int j);
        
        /// @brief Get a column of Pixel in an Image based on its index
        /// @param j  The column index
        /// @return The desired column of Pixel
        std::vector<Pixel> get_column(unsigned int j) const;

        /// @brief  Get channels of the image as a 1D collection of positive integers.
        /// This method returns a band of the image as a list. The only argument is the band index.
        /// @param b channel index
        /// @return vector<unsigned int> All values of the image on channel 'b' from left to right, top to bottom, concatenaed in a 1D array.
        std::vector<unsigned int> get_band_1D(unsigned int b) const;
        
        /// @brief Provides a set of matrices, each of them containingone band of the image. 
        /// @return std::vector<MatrixXcd> a vector of Eigen::MatrixXcd
        std::vector<MatrixXcd> bands_as_complex_matrices() const;

};  

/// @brief Function that converts a vector of MatrixXcd to a vector<vector<Pixel>>
/// @param bands_mat The matrices for each channel
/// @return std::vector<std::vector<Pixel>>, which can be used to construct an Image.
std::vector<std::vector<Pixel>> bands_matrix_to_2D_pixel_vector(std::vector<MatrixXcd> const& bands_mat);

