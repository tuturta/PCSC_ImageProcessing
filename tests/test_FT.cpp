#include "../src/transform.hh"
#include "../src/reader.hh"
#include "../src/writer.hh"
#include "../src/Image.hh"
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using Eigen::MatrixXcd;
using Eigen::VectorXcd;


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
    fft.fwd(test);
    cout << "Vector after FFT: \n" << test << endl;
    //test = test.head(5);
    // Apply IFFT
    //padToPowerOfTwo(test);
    fft.inv(test);
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
    fft.fwd(complexMatrix);
    cout << "Matrix after FFT: \n" << complexMatrix << endl;

    // Apply IFFT
    fft.inv(complexMatrix);
    cout << "Matrix after IFFT: \n" << complexMatrix << endl;

    // Import an image
    cout << "Start" << endl;
    const string path_in("in/test.ppm");
    const string path_out_gauss("out/blur.ppm");
    const string path_out_contour("out/contour.ppm");


    // Declaration of reader and writer classes
    PPMReader in_file(path_in);

    cout << "Classes initialized" << endl;

    try{
        // Create the image based on the input txt file
        Image image_blur(in_file.read());
        Image image_contour(in_file.read());
        
        // Create filters
        GaussianFilter filter_gauss(image_blur);
        ContourExtraction filter_solber(image_contour);

        // Apply filters
        cout << "APPLY filters" << endl;
        filter_gauss.apply();
        filter_solber.apply();

    // Save the image to the output file
        PPMWriter out_blur(path_out_gauss, image_blur);
        PPMWriter out_contour(path_out_contour, image_contour);
        out_blur.write();
        out_contour.write();

        cout << "Image written" << endl;
    }
    catch(std::exception& e){
        cerr << "ERREUR: " << e.what() << endl;
    }

    
    
    return 0;
}
