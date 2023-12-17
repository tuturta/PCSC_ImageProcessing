#include "transform.hh"
#include "Image.hh"
#include "MyExceptions.hh"
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using Eigen::MatrixXcd;
using Eigen::VectorXcd;

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


/*========Classes FourierTransform=======*/

void FourierTransform::fwd(MatrixXcd& image){
    // Shape of the image
    const size_t nb_rows(image.rows());
    const size_t nb_cols(image.cols());

    // test if the size is a power of two
    size_t test_power_of_two(1);
    while(test_power_of_two<nb_rows){
        test_power_of_two*=2;
    }
    if(test_power_of_two != nb_rows) throw std::domain_error("The number of rows is " + to_string(nb_rows) + " which is not a power of two !");
    
    test_power_of_two = 1;
    while(test_power_of_two<nb_cols){
        test_power_of_two*=2;
    }
    if(test_power_of_two != nb_cols) throw std::domain_error("The number of cols is " + to_string(nb_rows) + " which is not a power of two !");

    // Declare an empty row 
    VectorXcd row;

    // Apply FFT on every rows
    for(size_t i(0); i<nb_rows; ++i){
        row = image.row(i);
        this->fwd(row);
        image.row(i) = row;
    }   

    // Transpose the image
    image.transposeInPlace();

    // Apply FFT on every cols (columns are now rows because of the transposition)
    for(size_t i(0); i<nb_cols; ++i){
        row = image.row(i);
        this->fwd(row);
        image.row(i) = row;
    }  

    // Transpose back the image
    image.transposeInPlace();
}

void FourierTransform::inv(MatrixXcd& image){


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
        this->inv(row);
        image.row(i) = row;
    }   

    // Transpose back the image
    image.transposeInPlace();

    // Apply FFT on every cols (columns are now rows because of the transposition)
    for(size_t i(0); i<nb_rows; ++i){
        row = image.row(i);
        this->inv(row);
        image.row(i) = row;
    }  

    
}


// inverse Fourier Transform
void FourierTransform::inv(VectorXcd& complex_vector)
{   
    // conjugate the complex numbers
    complex_vector.conjugate();

    // forward fft
    this->fwd(complex_vector);
 
    // conjugate the complex numbers and scale it
    complex_vector.conjugate();
    complex_vector /= complex_vector.size();

    // shifting to the left in order to retrieve the initial order
    const complex<double> first = complex_vector[0];
    complex_vector.head(complex_vector.size() - 1) = complex_vector.tail(complex_vector.size() - 1);
    complex_vector[complex_vector.size() - 1] = first;
    complex_vector.reverseInPlace();
}

void FFT::fwd(VectorXcd& input){
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
    this->fwd(even);
    this->fwd(odd);

    // Calculate DFT
	for (size_t k = 0; k < len / 2; k++) {
        complex<double> t = polar(1., -2. * M_PI * k / len) * odd[k];
		input[k] = even[k] + t;
		input[len / 2 + k] = even[k] - t;
	}

}


/*DFT : Exact fourier transform*/
void DFT::fwd(VectorXcd& input)
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

void FFT::fwd(MatrixXcd& image){
    FourierTransform::fwd(image);
}

void DFT::fwd(MatrixXcd& image){
    FourierTransform::fwd(image);
}

/*=======Classes Filter=======*/

Filter::Filter(Image& image): image_(image) {}
ContourExtraction::ContourExtraction(Image& image): Filter(image) {
    array<size_t, 2UL> shape = image_.shape();
    if((shape[0]<3) or shape[1]<3) throw MinImageSizeException("Image can not be inferior to 3x3 !");
    if(shape[0] != shape[1]) throw RectangleImageException("Image can not be inferior to 3x3 !");

}
GaussianFilter::GaussianFilter(Image& image): Filter(image), sigma_(1), filter_size_(3)  {}
GaussianFilter::GaussianFilter(Image& image, double sigma, size_t filter_size): Filter(image), sigma_(sigma), filter_size_(filter_size){
    array<size_t, 2UL> shape = image_.shape();
    if((filter_size > shape[0]) or (filter_size > shape[1])) throw invalid_argument("The filter_size is larger than the image !");
    if(sigma < 0) throw invalid_argument("Sigma can not be negative !");
}


void ContourExtraction::apply(){

    // Extract the different channels
    vector<MatrixXcd> images = image_.bands_as_complex_matrices();

    // Compute size of image 
    size_t nb_cols = images[0].cols();
    size_t nb_rows = images[0].rows();

    // Sobel operator for horizontal and vertical edges
    MatrixXcd sobelX(3, 3);
    sobelX << -1, 0, 1,
              -2, 0, 2,
              -1, 0, 1;

    MatrixXcd sobelY = sobelX.transpose();

    // Apply sobel filter to all images
    MatrixXcd edgesX;
    MatrixXcd edgesY;
    for(auto& image : images){
        edgesX = applyFilter(image, sobelX);
        edgesY = applyFilter(image, sobelY);
        image = (edgesX.array().abs() + edgesY.array().abs()).matrix();
    }

    // Modify the attribute image
    image_ = Image(images); 
}

void GaussianFilter::apply(){
   
    // Extract the different channels
    vector<MatrixXcd> images = image_.bands_as_complex_matrices();

    // Parameters of the filter
    size_t filterSize = filter_size_;  // Adjust the filter size as needed
    double sigma = sigma_;      // Adjust the sigma value as needed
    
    // Create a 2D Gaussian filter
    MatrixXcd gaussianFilter(filterSize, filterSize);
    
    for (int i = 0; i < filterSize; ++i) {
        for (int j = 0; j < filterSize; ++j) {
            int x = i - filterSize / 2;
            int y = j - filterSize / 2;
            gaussianFilter(i, j) = std::exp(-(x * x + y * y) / (2 * sigma * sigma));
        }
    }

    // Normalize the Gaussian filter
    gaussianFilter /= gaussianFilter.sum();

    // Filtered images
    for(auto& image : images){
        image = applyFilter(image, gaussianFilter);
    }

    // Modify the attribute image
    image_ = Image(images);
}

MatrixXcd applyFilter(const MatrixXcd& input, const MatrixXcd& filter) {

    if (filter.size() > input.size()) throw std::domain_error("The filter is larger than the image !");

    // Apply 2D FFT to the input matrix
    FFT fft;

    // Zero padding to apply filter
    size_t padding_size = filter.rows()/2;
    MatrixXcd padded_matrix(input);


    // Padding in order to have size of power of 2 to Cooley Tukey Algorithm
    bool padding = padToPowerOfTwo(padded_matrix);     // Add padding to use FFT 
    fft.fwd(padded_matrix);

    // Pad the filter
    MatrixXcd filterX = MatrixXcd::Zero(padded_matrix.rows(), padded_matrix.cols());
    filterX.topLeftCorner(filter.rows(), filter.cols()) = filter;

    // Create frequency domain representations of operators
    fft.fwd(filterX);

    // Multiply in frequency domain (equivalent to convolution in spatial domain)
    padded_matrix = padded_matrix.cwiseProduct(filterX);

    // Apply inverse FFT to get back to spatial domain
    fft.inv(padded_matrix);

    // Remove the padding
    MatrixXcd out_matrix(input);
    out_matrix.block(padding_size+1, padding_size+1, out_matrix.rows()-padding_size-1, out_matrix.cols() - padding_size -1) =
    padded_matrix.block(padding_size+1, padding_size+1, out_matrix.rows()-padding_size-1, out_matrix.cols() - padding_size -1);

    return out_matrix;
}