#include "compute.hh"
#include "Image.hh"

// constructor of Compute
Compute::Compute(Image& img): data(img){};

// construcor of Contour_extraction
Contour_extraction::Contour_extraction(Image& img):Compute(img){};

// override pure virtual method 'compute' 
void Contour_extraction::compute(){
    
}