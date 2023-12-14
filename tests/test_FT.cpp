#include "../src/transform.hh"
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;


int main(){

    // Creation of a vector
    VectorXcd test(3);
    test << 1. , 2., 3.;
    cout << "Vector before any transormation: \n" << test << endl;
    // Pad to 2 
    padToPowerOfTwo(test);
    cout << "Vector padded: \n" << test << endl;
    // Apply FFT
    FFT fft;
    fft.transform(test);
    cout << "Vector after FFT: \n" << test << endl;
    //test = test.head(5);
    // Apply IFFT
    //padToPowerOfTwo(test);
    fft.inverse_transform(test);
    cout << "Vector after IFFT: \n" << test << endl;

    // Initialize a complex matrix with specified values
    Eigen::MatrixXcd complexMatrix(3, 3);  // A 3x3 complex matrix initialized with default values
    complexMatrix << std::complex<double>(1, 0), std::complex<double>(2, 0), std::complex<double>(3, 0),
                     std::complex<double>(4, 0), std::complex<double>(5, 0), std::complex<double>(6, 0),
                     std::complex<double>(7, 0), std::complex<double>(8, 0), std::complex<double>(9, 0);

    std::cout << "Complex Matrix:\n" << complexMatrix << "\n\n";

    padToPowerOfTwo(complexMatrix);
    std::cout << "Padded Complex Matrix:\n" << complexMatrix << "\n\n";
    // Apply fft
    fft.transform(complexMatrix);
    cout << "Matrix after FFT: \n" << complexMatrix << endl;

    // Apply IFFT
    fft.inverse_transform(complexMatrix);
    cout << "Matrix after IFFT: \n" << complexMatrix << endl;

    return 0;
}
