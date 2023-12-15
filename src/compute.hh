#pragma once
#include "Image.hh"

class Compute{
    public:
    Compute(Image const& img);

    protected:
    Image const& data;
};

class ComputeHistogram : public Compute {
    public:
    ComputeHistogram(Image const& img,unsigned int Nbins);
    std::vector<std::vector<double>> compute() const;
    
    private:
    unsigned int Nbins;
};