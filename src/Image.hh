#include "Pixel.hh"
#include<vector>
#include<array>

using namespace std;

// Class image
class Image{
    // Constructors
    public: 
        Image(vector<vector<Pixel>> const& data):data(data){}
        Image(Image const& img):data(img.data){} // copy constructor
    // operators :
        friend ostream & operator << (ostream &out, const Image &img); 

    // Attributes
    private:
        vector<vector<Pixel>> data;  
    // Methods 
    public : 
        array<size_t,2> shape() const;
        void set_pixel(Pixel const& P,unsigned int i, unsigned int j);
        Pixel get_pixel(unsigned int i, unsigned int j) const;  
};  