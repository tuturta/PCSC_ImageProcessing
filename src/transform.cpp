#include "transform.hh"
#include "Image.hh"
#include "MyExceptions.hh"
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;


bool padToPowerOfTwo(Eigen::VectorXcd& input) {
    size_t new_size = 1;
    const size_t old_size = input.size();
    while (new_size < old_size) {
        new_size *= 2;
    }
    if(new_size != old_size){
        input.conservativeResize(new_size);
        input.tail(new_size-old_size).setZero();
        return true;
    }else return false;
}

bool padToPowerOfTwo(Eigen::MatrixXcd& input) {
    size_t new_row_size = 1;
    size_t new_col_size = 1;
    const size_t row_size = input.rows();
    const size_t col_size = input.cols();

    while (new_row_size < row_size) {
        new_row_size *= 2;
    }
    while (new_col_size < row_size) {
        new_col_size *= 2;
    }
    
    if((new_row_size != row_size) and (new_col_size != col_size)){
        MatrixXcd padded_matrix = MatrixXcd::Zero(new_row_size, new_col_size);
        padded_matrix.topLeftCorner(input.rows(), input.cols()) = input;
        input = padded_matrix;
        return true;
    }else return false;
}



void FourierTransform::transform(MatrixXcd& image){

    // Shape of the image
    const size_t nb_rows(image.rows());
    const size_t nb_cols(image.cols());
    
    // Declare an empty row 
    VectorXcd row;

    // Apply FFT on every rows
    for(size_t i(0); i<nb_rows; ++i){
        row = image.row(i);
        this->transform(row);
        image.row(i) = row;
    }   

    // Transpose the image
    image.transposeInPlace();

    // Apply FFT on every cols (columns are now rows because of the transposition)
    for(size_t i(0); i<nb_cols; ++i){
        row = image.row(i);
        this->transform(row);
        image.row(i) = row;
    }  

    // Transpose back the image
    image.transposeInPlace();
}

void FourierTransform::inverse_transform(MatrixXcd& image){


    // Shape of the image
    const size_t nb_rows(image.rows());
    const size_t nb_cols(image.cols());
    
    // Declare an empty row 
    VectorXcd row;

    // Transpose the image
    image.transposeInPlace();

    // Apply FFT on every rows
    for(size_t i(0); i<nb_cols; ++i){
        row = image.row(i);
        this->inverse_transform(row);
        image.row(i) = row;
    }   

    // Transpose back the image
    image.transposeInPlace();

    // Apply FFT on every cols (columns are now rows because of the transposition)
    for(size_t i(0); i<nb_rows; ++i){
        row = image.row(i);
        this->inverse_transform(row);
        image.row(i) = row;
    }  

    
}


// inverse Fourier Transform
void FourierTransform::inverse_transform(VectorXcd& complex_vector)
{   
    // conjugate the complex numbers
    complex_vector.conjugate();

    // forward fft
    this->transform(complex_vector);
 
    // conjugate the complex numbers and scale it
    complex_vector.conjugate();
    complex_vector /= complex_vector.size();

    // shifting to the left in order to retrieve the initial order
    const complex<double> first = complex_vector[0];
    complex_vector.head(complex_vector.size() - 1) = complex_vector.tail(complex_vector.size() - 1);
    complex_vector[complex_vector.size() - 1] = first;
    complex_vector.reverseInPlace();
}

void FFT::transform(VectorXcd& input){
    const size_t len(input.size());

    // Check if it is splitted enough
	if (len <= 1) {
		return;
	}
    
    VectorXcd odd(len/2);
    VectorXcd even(len/2);

	// Split into even and odd vectors
    for (int i(0); i < len/2; ++i) {
        even[i] = input[2*i];
        odd[i]  = input[2*i + 1];
    }

    // Recursively call the Fourier Transform until the len is 1 
    this->transform(even);
    this->transform(odd);

    // Calculate DFT
	for (size_t k = 0; k < len / 2; k++) {
        complex<double> t = polar(1., -2. * M_PI * k / len) * odd[k];
		input[k] = even[k] + t;
		input[len / 2 + k] = even[k] - t;
	}

}


/*DFT : Exact fourier transform*/
void DFT::transform(VectorXcd& input)
{
	complex<double> temp;
    const complex<double> i(0.,1.);
    const complex<double> null(0., 0.);
    const double size = static_cast<double>(input.size());

	for(size_t k=0; k<input.size(); k++)
	{   
        temp = null;
		for(size_t n=0; n<input.size(); n++)
		{
			temp += input[n]*exp(-i*2.*M_PI*(double)k*(double)n/size);
		}
		input[k] = temp/size;
	}
}

void FFT::transform(MatrixXcd& image){
    FourierTransform::transform(image);
}

void DFT::transform(MatrixXcd& image){
    FourierTransform::transform(image);
}