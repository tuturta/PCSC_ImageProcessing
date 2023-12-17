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


    // Import an image
    cout << "Start" << endl;
    const string path_in("in/test_photo.ppm");
    const string path_out_gauss("out/blur_parrot.ppm");
    const string path_out_contour("out/contour_parrot.ppm");


    // Declaration of reader and writer classes
    PPMReader in_file(path_in);

    cout << "Classes initialized" << endl;

    try{
        // Create the image based on the input txt file
        Image image_blur(in_file.read());
        Image image_contour(in_file.read());
        
        // Create filters
        GaussianFilter filter_gauss(image_blur, 10, 3);
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
