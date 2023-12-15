#include "compute.hh"
#include "Image.hh"

// constructor of Compute
Compute::Compute(Image const& img): data(img){};

// Constructor of ComputeHistogram 
ComputeHistogram::ComputeHistogram(Image const& img, unsigned int Nbins):Compute(img),Nbins(Nbins){};

/**
 * @brief Computes the intensity histograms for each channel of an image.
 * 
 * @return std::vector<std::vector<double>> vector containing the histograms for each channel
 */
std::vector<std::vector<double>> ComputeHistogram::compute() const{
    // Dimensions of the image
    size_t Nbands(data.Nbands());
    std::array<size_t,2> shape(data.shape());
    
    double contribution_per_pixel(1.0/(shape[0]*shape[1])); 
    
    // Initialize the histograms 
    std::vector<double> init_histogram(Nbins,0.0);
    std::vector<std::vector<double>> histograms(Nbands,init_histogram);

    // Compute the histograms values
    double max(data.get_max()); // implicit conversion to double
    double k(Nbins-1);
    double a(k/max);

    for(size_t i(0);i<shape[0]; ++i){
        for(size_t j(0);j<shape[1];++j){
            for(size_t channel(0); channel<Nbands;++channel){
                unsigned int channel_value(data.get_pixel(i,j).get_channel_value(channel));
                unsigned int bin(floor(a*channel_value));
                histograms[channel][bin]+=contribution_per_pixel;
            }
        }
    } 
    return histograms;
}



