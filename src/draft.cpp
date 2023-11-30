#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>


using namespace std;


// Class Pixel : a pixel is a collection of N positive integers (e.g. N=1 for grayscale pixel, N=3 for RGB pixel,...)
class Pixel{
    // Constructor
    public :
        Pixel(initializer_list<uint8_t> const& val): values(val){}
        Pixel(vector<uint8_t> channels): values(channels){}
    // Methods 
    public : 
        size_t dim();
        void set_channel_value(size_t channel_id, uint8_t value);
        uint8_t get_channel_value(size_t channel_id) const;
    // Attributes 
    private :
        vector<uint8_t> values;
};

// Definitions of the methods:

size_t Pixel::dim(){
    // Returns the dimension of the pixel
    return values.size();
}

void Pixel::set_channel_value(size_t channel_id, uint8_t value){ 
    // Set the channel 'channel_id' to the value 'value'
    values[channel_id]=value;
}

uint8_t Pixel::get_channel_value(size_t channel_id) const{
    // Returns the value stored in channel number 'channel_id'
    return values[channel_id];
}


vector<vector<Pixel>> readTXT(string path){
    int input;
    ifstream file;
    file.open(path);
    if(file.fail()){
        cerr << "L'ouverture du fichier a fail!" << endl;
    }
    size_t nb_rows, nb_cols, nb_channels;
    vector<uint8_t> channels;
    vector<Pixel> cols;
    vector<vector<Pixel>> image;
     
    file >> nb_rows >> nb_cols >> nb_channels;
    file >> ws;

    for(size_t row = 0; row < nb_rows; ++row){
        for(size_t col = 0; col < nb_cols; ++col){
            for(size_t i = 0; i < nb_channels; ++i){
                file >> input;
                if(input < 0 or input>255){
                    cerr << "Un des channels a une valeur supérieur à 255" << endl;
                }
                channels.push_back((uint8_t) input);
                // Si on est à la fin du fichier, arrêter la lecture
                if(file.eof()){
                    cerr << "La taille spécifiée et les données ne correspondent pas !" << endl;
                }
            }
            cols.push_back(Pixel(channels));
            channels.clear();           
        }
        image.push_back(cols);
        cols.clear();
    } 
    file.close();
    return image;
}


// Structure to store RGB values
struct Pixel2 {
    int red;
    int green;
    int blue;
};

// Function to read a PPM image and convert it to a 2D vector
vector<vector<Pixel>> readPPMImage(const string& filename) {
    vector<uint8_t> pixels;
    vector<Pixel> cols;
    vector<vector<Pixel>> image;
    int red, green, blue;

    // Open the PPM file
    ifstream ppmFile(filename, ios::binary); // Open in binary mode for binary PPM files

    if (!ppmFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        // You can handle the error as per your requirement
        return image;
    }

    // Read the PPM header
    string magicNumber;
    ppmFile >> magicNumber;

    if (magicNumber != "P3") {
        cerr << "Unsupported PPM format. This example supports only P3 format." << endl;
        return image;
    }

    int width, height, maxColor;
    ppmFile >> width >> height >> maxColor;

    // Read pixel values
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ppmFile >> red >> green >> blue;
            cols.push_back(Pixel{(uint8_t) red, (uint8_t) green, (uint8_t) blue});
        }
        image.push_back(cols);
        cols.clear();
    }

    // Close the file
    ppmFile.close();

    return image;
}

// Function to write a PPM P3 file from a 2D vector of pixels
void writePPMP3(const string& filename, const vector<vector<Pixel>>& image) {
    // Open the PPM file for writing
    ofstream ppmFile(filename, std::ofstream::out | std::ofstream::trunc);

    if (!ppmFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        // You can handle the error as per your requirement
        return;
    }

    // Write PPM header
    ppmFile << "P3\n";
    ppmFile << image[0].size() << " " << image.size() << "\n";
    ppmFile << "255\n"; // Assuming max color value is 255

    // Write pixel values
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            ppmFile << unsigned(pixel.get_channel_value(0)) << " " << unsigned(pixel.get_channel_value(1)) << " " << unsigned(pixel.get_channel_value(2)) << " ";
        }
        ppmFile << "\n"; // Newline after each row
    }

    // Close the file
    ppmFile.close();

    cout << "PPM P3 file written successfully: " << filename << endl;
}

int main(){

    string path_txt("../in/test.txt");
    vector<vector<Pixel>> image1 = readTXT(path_txt);

    // Specify the PPM file name
    string filename = "../in/test.ppm";

    // Call the function to read the PPM image
    vector<vector<Pixel>> image2 = readPPMImage(filename);

    // Call the function to write PPM image
    string path = "../out/out.ppm";
    writePPMP3(path, image2);

    return 0;
}