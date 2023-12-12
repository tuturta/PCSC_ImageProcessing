#include "writer.hh"
#include "MyExceptions.hh"
#include <fstream>
#include <string>


AbstractWriter::AbstractWriter(string_view path):path_(path){}
TXTWriter::TXTWriter(string_view path):AbstractWriter(path){}
PPMWriter::PPMWriter(string_view path):AbstractWriter(path){}


// Function to write a PPM P3 file from a 2D vector of pixels
void PPMWriter::write(const Image& image) {
    // Open the PPM file for writing
    ofstream ppmFile(path_, std::ofstream::out | std::ofstream::trunc);

    if (!ppmFile.is_open()) {
        throw ifstream::failure("Error opening file: " + path_ );
    }

    // Shape of the image 
    auto shape(image.shape());
    vector<Pixel> row;

    // Write PPM header
    ppmFile << "P3\n";
    ppmFile << shape[1] << " " << shape[0] << "\n";
    ppmFile << "255\n"; // Assuming max color value is 255

    // Write pixel values
    for (size_t i = 0; i<shape[0]; ++i) {
        row = image.get_row(i);
        for (const auto& pixel : row) {
            ppmFile << unsigned(pixel.get_channel_value(0)) << " " << unsigned(pixel.get_channel_value(1)) << " " << unsigned(pixel.get_channel_value(2)) << " ";
        }
        ppmFile << "\n"; // Newline after each row
    }

    // Close the file
    ppmFile.close();
}

// Function to write a PPM P3 file from a 2D vector of pixels
void TXTWriter::write(const Image& image) {
    
    // Open the PPM file for writing
    ofstream txtFile(path_, std::ofstream::out | std::ofstream::trunc);
    if (!txtFile.is_open()) {
        throw ifstream::failure("Error opening file: " + path_ );
    }
   
   // Shape of the image 
    auto shape(image.shape());
    
    // Initialize a new vector row
    vector<Pixel> row;
    
    // Write txt header
    txtFile << shape[1] << " " << shape[0] << " " << image.get_pixel(0,0).dim() << "\n";

    // Write pixel values
    for (size_t i=0; i<shape[0]; ++i) {
        row = image.get_row(i);
        for (const auto& pixel : row) {
            txtFile << unsigned(pixel.get_channel_value(0)) << " " << unsigned(pixel.get_channel_value(1)) << " " << unsigned(pixel.get_channel_value(2)) << "   ";
        }
        txtFile << "\n"; // Newline after each row
    }
    
    // Close the file
    txtFile.close();
}