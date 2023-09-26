/* 
c++ -o main checks.cc muon_class.cc main.cpp `root-config --glibs --cflags`
./main 9.5
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

#include "TGraph2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPad.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "checks.h"
#include "muon_class.h"


#define L 171.5 //distance between the 2 detectors in cm
#define N 1e8 //tries
#define width 80.0 //in cm
#define depth 30.0 //in cm



int main (int argc, char ** argv){

    TApplication theApp("theApp", &argc, argv);
    srand(time(NULL)); 
    double path_lenght;

    TH1F h_path("171.5 cm", " ", sqrt(sqrt(N)), L - 1, 192);
    TH2F h2_positions("171.5 cm", " ", 160, -40, 40, 60, -15, 15); // nbinx minx maxx nbiny miny maxy

    int j=0;
    int counts = 0;
    int counts_vertical = 0;

    while (j < N){
      Muon muon(rand_theta(f_cos2, -M_PI/2, 0, 4/M_PI), rand_phi(0, 2*M_PI)); /*distribuzione cos^2*/
      double x0 = rand_range(-width / 2, width / 2);
      double y0 = rand_range(-depth / 2, depth / 2);
      if (is_coincidence(L, muon.coeff_x(), muon.coeff_y(), x0, y0) == true)
      {
        path_lenght = get_path(L, muon.coeff_x(), muon.coeff_y(), rand_range(-width / 2, width / 2), rand_range(-depth / 2, depth / 2));
        h_path.Fill(path_lenght);
        h2_positions.Fill(x_coinc_coord(L, muon.coeff_x(), x0), y_coinc_coord(L, muon.coeff_y(), y0));
  
        counts++;
        if( check_vertical(muon.get_theta()) ){
          counts_vertical ++;
        }

      }
      if (j % 10000000 == 0){
      	std::cout << "Done/Total: \t" << j << "/" << N << "\n";
      }
      j++;
    }
    

    std::cout.precision(3);
    std::cout << "il " << counts*100./pow(10, 8) << " % " << " di " << N << " muons passed through the second detector afted being detected by the first" << "\n" ;
    std::cout << "il " << counts_vertical*100./counts << " % " << " di " << N << " muons had inclination between 0 and 1 steradiant" << "\n" ;

    std::ofstream outfile_mean("distances.txt", std::ios::app);
    if (outfile_mean.is_open())
    {
      outfile_mean << h_path.GetMean(1) << "\t" << h_path.GetStdDev(1) << "\t" << L << std::endl;
      outfile_mean.close();
    }

   // TH1D * projh2X = h2_positions.ProjectionX();
   // TH1D * projh2Y = h2_positions.ProjectionY();

    gStyle->SetPalette(1);

    TCanvas c1;
    c1.SetLeftMargin(.15);
    c1.SetBottomMargin(.15);


    h_path.GetXaxis()->SetTitle(" distanza percorsa [cm]");
    h_path.GetYaxis()->SetTitle(" counts ");
    h_path.GetXaxis()->SetTitleSize(0.07);
    h_path.GetYaxis()->SetTitleSize(0.07);
    h_path.GetXaxis()->SetLabelSize(0.05);
    h_path.GetYaxis()->SetLabelSize(0.05);
    h_path.SetFillColor (kOrange + 1) ;
    h_path.Draw ();
    std::string fileDistanze = "distribution_distances_";
    std::string lenght = argv[1];
    std::string extension = ".pdf";
    c1.SetLogy();
   // c1.Print ((fileDistances+lenght+extension).c_str(), "pdf") ;
   

    TCanvas c2;
    c2.SetLeftMargin(.15);
    c2.SetBottomMargin(.15);
    c2.SetRightMargin(.15);
    gStyle->SetPalette(57);
    h2_positions.GetXaxis()->SetLabelSize(0.05);
    h2_positions.GetYaxis()->SetLabelSize(0.05);

    h2_positions.Draw("COLZ1");
    std::string fileDistribution = "distribution2D_";
    c2.Print((fileDistribution+lenght+extension).c_str(), "pdf");
     return 0;
  }
