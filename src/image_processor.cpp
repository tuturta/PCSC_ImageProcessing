#include "reader.hh"
#include "Pixel.hh"
#include "Image.hh"
#include "transform.hh"
#include "plot_histogram.hh"
#include "compute.hh"
#include "writer.hh"
#include <stdexcept>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc>=3){
        string filename(argv[1]);
        string process_to_apply(argv[2]);

        try{
            PPMReader reader("../in/"+filename+".ppm");
            Image image(reader.read());

            if(process_to_apply=="plot_hist"){
                string output_path("../output/histogram_"+filename);
                unsigned int Nbins(0);
                
                cout << "Set the number of bins (positive integer, e.g. 256) : ";
                cin >> Nbins;
                draw_histogram(image,output_path,Nbins);

            }else if(process_to_apply=="compute_hist"){
                unsigned int Nbins(0);
                cout << "Set the number of bins (positive integer, e.g. 256) : ";
                cin >> Nbins;
                // Compute histograms 
                ComputeHistogram compute_histograms(image,Nbins);    
                vector<vector<double>> histograms_computed(compute_histograms.compute());
                
                // Write in txt file 
                ofstream outputfile("../output/histograms_per_band_"+filename+".txt");
                for(size_t i (0); i < histograms_computed.size(); ++i) {
                    for(size_t j(0);j<histograms_computed[i].size();++j){
                        outputfile << histograms_computed[i][j] << " " ;
                    }
                    outputfile << endl;
                }
            }else if(process_to_apply=="contour_extraction"){
                ContourExtraction filter_solber(image);
                filter_solber.apply();
                
                PPMWriter out_contour("../output/contour_extracted_"+filename+".ppm", image);
                out_contour.write();

            }else if(process_to_apply=="noise_removal"){
                GaussianFilter filter_gauss(image);
                PPMWriter out_blur("../output/gaussian_noise_removal_"+filename+".ppm", image);
                
                filter_gauss.apply();
                out_blur.write();
            } else {
                invalid_argument error("Invalid process name. Should be plot_hist, compute_hist, contour_extraction, or noise_removal");
                throw error;
            }
        }
        catch(exception error){
            cerr << "Exception catched : " << error.what() << endl;
            return 2;
        }
        return 0;
    } else {
        cerr << "You should provide line arguments <image_name.ppm> and <process_to_apply> to run this executable" << endl;
        return 1;
    }
}