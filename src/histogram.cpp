#include "MyExceptions.hh"
#include "Image.hh"
#include<iostream>
#include "../gnuplot-iostream/gnuplot-iostream.h"
#include<string>
#include<iostream>
using namespace std;

/**
 * @brief Draws the intensity histogram of the Image passed in argument, for all of its channels.
 * 
 * @param image
 * @param fp 
 * @param Nbins 
 */
void draw_histogram(Image const& image,string fp,unsigned int Nbins=50){
    size_t Nbands(image.Nbands());
    array<size_t,2> shape=image.shape();

    vector<vector<unsigned int>> bands_1D;
    for(size_t b(0); b< Nbands; ++b){
        bands_1D.push_back(image.get_band_1D(b));
    }
    
    Gnuplot gp;
    gp << "reset\n";
    gp << "n=260\n";
    gp << "max=260\n";
    gp << "min=0\n";
    gp << "width=(max-min)/"<< Nbins <<"\n"; 
    /// function used to map a value to the intervals
    gp << "hist(x,width)=width*floor(x/width)+width/2.0\n";
    gp << "set xrange [min:max]\n";
    gp << "set yrange [0:]\n";
    /// to put an empty boundary around the data inside an autoscaled graph.
    gp << "set offset graph 0.05,0.05,0.05,0.0\n";
    gp << "set xtics min,(max-5-min)/5,max-5\n";
    gp << "set boxwidth width*0.9\n";
    gp << "set style fill transparent solid 0.5\n";
    gp << "set style data histograms\n";

    /// Grid
    gp << "set style line 81 lt 0 lc rgb '#808080' lw 0.5\n";
    gp << "set grid xtics\n";
    gp << "set grid ytics\n";
    gp << "set grid back ls 81\n";

    gp << "set tics out nomirror\n";
    gp << "set xlabel 'Channel value'\n";
    gp << "set ylabel 'Count'\n";

    /// Plot
    for(size_t b(0);b<Nbands;++b){
        if(b==0){
            gp << "plot ";
        }
        gp << "'-' u (hist($1,width)):(1.0) smooth freq w boxes title 'Channel " << b << "'";
        
        if(b<Nbands-1){
            gp << ",";
        } else if(b==Nbands -1){
            gp << "\n";
        }
    }
    for(size_t b(0);b<Nbands;++b){
        gp.send1d(bands_1D[b]);
    }
    /// Save the histograms as png figures
    gp << "set terminal pngcairo\n";
    gp << "set output '" << fp << ".png'\n";
    gp << "replot\n" ;
    gp << "set terminal wxt\n" ;
    gp << "set output\n";

}

