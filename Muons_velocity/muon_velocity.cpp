/*
c++ -o muon_velocity muon_velocity.cpp `root-config --glibs --cflags`
./muon_velocity 9.5cm 38.2cm 97.15cm 171.5cm
*/


#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <cmath>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TAxis.h"
#include "TFitResult.h"
#include "TStyle.h"
#include "TGraphPainter.h"
#include "TFrame.h"
#include "TGraphAsymmErrors.h"

double line (double * x, double * par)
  {
    return par[0] + par[1] * x[0] ;
  }

using namespace std;
int main(int argc, char* argv[]){
  TApplication theApp("theApp", &argc, argv);

  double m[] = {0.1221, 0.0008013}; // angular coefficient calibration line of TDC
  double q[] = {0.8727, 0.3014};    // offset calibration line of TDC
  
  gStyle->SetOptFit(1112);

  vector<double> TDC, TDC_err, TDC_errb, TDC_errt, dist, dist_err;
  double adc1, adc2, tdc, e_tdc, sum=0, weight, sumweights=0;
  TCanvas c1 ("c1", "c1", 100, 100, 1000, 1000) ;
  double corrected_parameters[4] = {11.22/9.5, 40.90/38.2, 99.21/97.15, 172.9/171.5};
  double distances[4] = {9.5, 38.2, 97.15, 171.5};
  double e_distances[4] = {1, 1, 1, 1};

  ifstream data_corrected;
  string fileData = "Data/data_tdcadc_";
	string extensionCorr = "_AWcorr.txt";
	
	for(int i = 0; i<4; i++){
    data_corrected.open((fileData+argv[i+1]+extensionCorr).c_str());
   
  	while(!data_corrected.eof()){
  		data_corrected >> tdc;
  		data_corrected >> e_tdc;
  		data_corrected >> adc1; //ignored
  		data_corrected >> adc2; //ignored
  		
  		weight = 1/pow(e_tdc, 2);
  		sum=sum+tdc*weight;
  		sumweights=sumweights+weight;
  	}
  	data_corrected.close();
  	  
    TDC.push_back(sum/sumweights);
    cout<<"tdc: "<<sum/sumweights<<endl;
    TDC_err.push_back(sqrt(1/sumweights));

    cout<<"err tdc: "<<sqrt(1/sumweights)<<endl;


    dist.push_back(distances[i]*corrected_parameters[i]/100.);
    //cout << "lenght corrected in metres: " << distances[i]*corrected_parameters[i]/100. << endl;
    dist_err.push_back(e_distances[i]*corrected_parameters[i]/100);
    //cout << "error lenght corrected in metres: " << e_distances[i]*corrected_parameters[i]/100 << endl;

   
    sum = 0; 
    sumweights = 0;
  }
	

  
  vector<double> TDC_errb_agg{0.4*m[0] + q[0], 0.1*m[0] + q[0], 0, 0.4*m[0] + q[0]};
  vector<double> TDC_errt_agg{0, 0, 0.1*m[0] + q[0], 0};

  for(int i = 0; i<4; i++){
    TDC_errb.push_back(TDC_err.at(i) + TDC_errb_agg.at(i));
    TDC_errt.push_back(TDC_err.at(i) + TDC_errt_agg.at(i));

  }

  TGraphAsymmErrors funz(dist.size (), &dist[0], &TDC[0], &dist_err[0], &dist_err[0], &TDC_errb[0], &TDC_errt[0]);
  
  //gae->Draw("a2");
  //gae->Draw("p");
	//TGraphErrors funz (dist.size (), &dist[0], &TDC[0], &dist_err[0], &dist_err[0], &TDC_errb[0], &TDC_errt[0]) ;
	funz.SetMarkerStyle (4) ;
	funz.SetMarkerColor (kRed) ;
	
	funz.GetXaxis()->SetTitle("distanze [m]");
  funz.GetYaxis()->SetTitle("tempi[ns]");
  funz.GetXaxis()->SetTitleSize(0.05);
  funz.GetYaxis()->SetTitleSize(0.05);

  funz.SetTitle(" ");
    
  TF1 f_fit ("f_fit", line, 0., 3., 2) ;
  f_fit.SetParNames("q", "m");

  TFitResultPtr fit_result = funz.Fit (&f_fit, "S") ;

  cout << endl ;
	cout.precision (7) ;
  cout << "risultato del fit: " << fit_result->IsValid () << endl ;
  cout << "termine noto : " << f_fit.GetParameter (0) << "\t+- " << f_fit.GetParError (0) << endl ;
  cout << "pendenza (inverso velocità muoni)     : " << f_fit.GetParameter (1) << "\t+- " << f_fit.GetParError (1) << endl ;
    
  cout<< "valore velocita: " << pow(10, 9)/f_fit.GetParameter (1) << "m/s +- " << f_fit.GetParError (1)*pow(10, 9)/pow(f_fit.GetParameter (1), 2) << "m/s" << endl;

  c1.SetLeftMargin(0.15);
  c1.SetBottomMargin(0.15);
  funz.Draw ("AP") ;
  c1.Print ("velocità_finale.pdf", "pdf") ; 

  theApp.Run();
  return 0;
}
