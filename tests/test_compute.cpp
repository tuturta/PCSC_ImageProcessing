#include "../src/Image.hh"
#include "../src/compute.hh"
#include <gtest/gtest.h>

using namespace std;

TEST(TestCompute,test_ComputeHistogram){
    Pixel p0({0,0,255});
    Pixel p1({0,50,255});
    Pixel p2({0,50,255});
    Pixel p3({0,50,255});
    Pixel p4({0,150,255});
    Pixel p5({0,150,255});
    Pixel p6({0,150,255});
    Pixel p7({0,150,255});
    Pixel p8({0,150,255});

    vector<vector<Pixel>> pix_2Dvector({{p0,p1,p2},{p3,p4,p5},{p6,p7,p8}});
    Image image(pix_2Dvector);
    unsigned int Nbins(256);
    
    // Compute histograms 
    ComputeHistogram compute_histograms(image,Nbins);    
    vector<vector<double>> histograms_computed(compute_histograms.compute());
    // Define the ground truth 
    vector<double> expect_hist0(Nbins,0.0);
    expect_hist0[0]=1.0;
    vector<double> expect_hist1(Nbins,0.0);
    expect_hist1[0]=1.0/9.0;
    expect_hist1[50]=1.0/3.0;
    expect_hist1[150]=5.0/9.0;

    vector<double> expect_hist2(Nbins,0.0);
    expect_hist2[255]=1.0;
    vector<vector<double>> histograms_expected({expect_hist0,expect_hist1,expect_hist2});

    // Perform the test :
    for(size_t channel(0);channel<3;++channel){
        for(size_t bin(0);bin<Nbins;++bin){
            EXPECT_NEAR(histograms_computed[channel][bin],histograms_expected[channel][bin],1e-6) << "Discrete probability for bin " << bin << " on channel " << channel ;
        }
    }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}