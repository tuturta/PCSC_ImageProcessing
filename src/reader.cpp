#include "reader.hh"
#include "MyExceptions.hh"
#include <fstream>

using namespace std;



AbstractReader::AbstractReader(string_view path): path_(path) {};
TXTReader::TXTReader(string_view path): AbstractReader(path) {};
PPMReader::PPMReader(string_view path): AbstractReader(path) {};

Image TXTReader::read(){
    int input;
    ifstream file;
    int nb_cols, nb_rows, nb_channels;
    vector<unsigned int> channels;
    vector<Pixel> cols;
    vector<vector<Pixel>> image;

    file.open(path_);

    // Check if the file has been opened correctly
    if(!file.is_open()) throw ifstream::failure("Error opening file: " + path_ );

    // Extract the shape of the data
    file >> nb_cols >> nb_rows >> nb_channels;
    file >> ws;
    for(size_t row = 0; row < nb_rows; ++row){
        for(size_t col = 0; col < nb_cols; ++col){
            for(size_t i = 0; i < nb_channels; ++i){
                if(file.eof()){
                    throw invalid_argument("Specified data size and actual data size do not match !");
                }
                file >> input;
                //cout << row << col << i << endl;
                if(input < 0){
                    string error_message("Negative input in the text file at position (" + to_string(row) + ", " + to_string(col) + ", " + to_string(i) + ")");
                    throw invalid_argument(error_message);
                }
                channels.push_back((unsigned int) input);
            }
            cols.push_back(Pixel(channels));
            channels.clear();           
        }
        image.push_back(cols);
        cols.clear();
    } 

    file.close();
    return Image(image);
}


Image PPMReader::read(){
    vector<unsigned int> pixels;
    vector<Pixel> cols;
    vector<vector<Pixel>> image;
    int red, green, blue;

    // Open the PPM file
    ifstream ppmFile(path_, ios::binary); // Open in binary mode for binary PPM files

    if (!ppmFile.is_open()) {
        throw ifstream::failure("Error opening file: " + path_ );
    }

    // Read the PPM header
    string magicNumber;
    ppmFile >> magicNumber;

    if (magicNumber != "P3") {
        throw invalid_argument("Unsupported PPM format. This example supports only P3 format.");
    }

    int nb_cols, nb_rows, maxColor;
    ppmFile >> nb_cols >> nb_rows >> maxColor;

    // Read pixel values
    for (int i = 0; i < nb_rows; ++i) {
        for (int j = 0; j < nb_cols; ++j) {
            ppmFile >> red >> green >> blue;
            if((red < 0) or (green < 0) or (blue < 0)){
                        string error_message("Negative input in the text file at position (" + to_string(i) + ", " + to_string(j) + ")");
                        throw invalid_argument(error_message);
                    }
            cols.push_back(Pixel{(unsigned int) red, (unsigned int) green, (unsigned int) blue});

            if(ppmFile.eof()){
                        throw invalid_argument("Specified data size and actual data size do not match !");
            }
        }
        image.push_back(cols);
        cols.clear();
    }

    // Close the file
    ppmFile.close();

    return image;
}