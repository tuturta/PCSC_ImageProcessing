#pragma once
#include "Image.hh"

class Compute{
    public:
    Compute(Image& img);

    protected:
    Image& data;

    public:
    virtual void compute()=0;
};

class Contour_extraction: public Compute{
    public:
    Contour_extraction(Image& img);
    virtual void compute() override;
};