#pragma once
#include"Image.hh"

/// @brief Parent class for classes used for extracting informations from Images
/** 
 * Has no methods and only one attribute, a const reference to an Image. The purpose of this class is to be inherited by daughter classes as ComputeHistogtram
 */
class Compute{
    public:
    /// Constructor of the class Compute
    /// @param img const reference to an Image
    Compute(Image const& img);

    protected:
    Image const& data;
};

/// @brief Class used to compute intensity histograms of Images
/** Inherits from class Compute. 
 * This class owns a method compute, which computes the histogram of the Image pointed by the referenced data. 
 */
class ComputeHistogram : public Compute {
    public:
    /// @brief Constructor of class ComputeHistogram
    /// @param img Const reference to the Image on which to compute the histogram
    /// @param Nbins Positive integer - This parameter determines the number of bins in the histogram to compute
    ComputeHistogram(Image const& img,unsigned int Nbins);
    
    ///@brief Computes the intensity histograms for each channel of an image.
    ///@return std::vector<std::vector<double>> vector containing the histograms for each channel
    std::vector<std::vector<double>> compute() const;
    
    private:
    unsigned int Nbins; /// Number of bins in the histogram
};