#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <complex>
#include <valarray>

using namespace std;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;


void fft1D(vector< complex<double> > & input); 
void ifft1D(vector<complex<double>>& input);
void dft(vector<complex<double>>& input);
void idft(vector<complex<double>>& input);
vector<complex<double>> to_complex(const vector<double> & input);

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
    size_t width, height, nb_channels;
    vector<uint8_t> channels;
    vector<Pixel> cols;
    vector<vector<Pixel>> image;
     
    file >> width >> height >> nb_channels;
    file >> ws;

    for(size_t row = 0; row < width; ++row){
        for(size_t col = 0; col < height; ++col){
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

// Function to write a PPM P3 file from a 2D vector of pixels
void writeTXT(const string& filename, const vector<vector<Pixel>>& image) {
    // Open the PPM file for writing
    ofstream txtFile(filename, std::ofstream::out | std::ofstream::trunc);

    if (!txtFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        // You can handle the error as per your requirement
        return;
    }

    // Write txt header
    txtFile << image[0].size() << " " << image.size() << "\n";

    // Write pixel values
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            txtFile << unsigned(pixel.get_channel_value(0)) << " " << unsigned(pixel.get_channel_value(1)) << " " << unsigned(pixel.get_channel_value(2)) << "   ";
        }
        txtFile << "\n"; // Newline after each row
    }

    // Close the file
    txtFile.close();

    cout << "Text file written successfully: " << filename << endl;
}



int main(){
    /*
    string path_txt("../in/test.txt");
    vector<vector<Pixel>> image1 = readTXT(path_txt);

    // Specify the PPM file name
    string filename = "../in/test.ppm";

    // Call the function to read the PPM image
    vector<vector<Pixel>> image2 = readPPMImage(filename);

    // Call the function to write PPM image
    string path_ppm = "../out/out.ppm";
    path_txt        = "../out/out.txt";
    writePPMP3(path_ppm, image2);
    writeTXT(path_txt, image1);
    */

    vector <double> test({1.       ,  2.,  3.,  4., 5. ,
       6., 7., 8. });
    cout << "vector : ( " ;
    for(auto const &x: test){
        cout << x << " ";
    }
    cout << ")" << endl; 

    vector < complex<double> > test_convert(to_complex(test));
    cout << "vector : ( " ;
    for(auto const &x: test_convert){
        cout << x << " ";
    }
    cout << ")" << endl; 

    fft1D(test_convert);

    cout << "vector fft : ( " ;
    for(size_t i = 0; i < test_convert.size(); ++i){
        cout << test_convert[i] << " ";
    }
    cout << ")" << endl; 

    ifft1D(test_convert);

    cout << "vector ifft : ( " ;
    for(size_t i = 0; i < test_convert.size(); ++i){
        cout << test_convert[i] << " ";
    }
    cout << ")" << endl; 
    
    vector < complex<double> > test_convert2(to_complex(test));
    dft(test_convert2);

    cout << "vector dft : ( " ;
    for(auto const &x: test_convert2){
        cout << x << " ";
    }
    cout << ")" << endl; 

    idft(test_convert2);

    cout << "vector idft : ( " ;
    for(auto const &x: test_convert2){
        cout << x << " ";
    }
    cout << ")" << endl; 
    
    return 0;

}

/* -------------  FFT : exact for power of 2 only  ---------------*/


void fft1D(vector< complex<double> > & input){
    const size_t len(input.size());

    // Check if it is splitted enough
	if (len <= 1) {
		return;
	}

	// Split even and odd
    vector< complex<double> > odd;
    vector< complex<double> > even;

    for(size_t i = 0; i < len/2; ++i){
        even.push_back(input[i*2]);
        odd.push_back(input[i*2+1]);
    }

    // Recursively call the Fourier Transform until the len is 1 
    fft1D(even);
    fft1D(odd);

    // Calculate DFT
	for (size_t k = 0; k < len / 2; k++) {
        complex<double> t = polar(1., -2. * M_PI * k / len) * odd[k];
		input[k] = even[k] + t;
		input[len / 2 + k] = even[k] - t;
	}
}

// inverse fft (in-place)
void ifft1D(vector<complex<double>>& input)
{
    // conjugate the complex numbers
    for(auto &x : input){
        x = conj(x);
    }

    // forward fft
    fft1D( input );
 
    // conjugate the complex numbers and scale it
    for(auto &x : input){
        x = conj(x);
        x /= input.size();
    }
}

vector<complex<double>> to_complex(const vector<double>& input){
    vector<complex<double>> out; 
    for(auto const &x: input){
        out.push_back(complex<double>(x, 0.));
    }
    return out;
}


/*DFT : Exact fourier transform*/
void dft(vector<complex<double>>& input)
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
		input[k] = temp/= input.size();
	}
}

/*IDFT : Exact inverse fourier transform*/
void idft(vector<complex<double>>& input)
{
    
    for(auto &x : input){
        x = conj(x);
    }

    dft(input);

    for(auto &x : input){
        x = conj(x);
        //x /= input.size();
    }

}