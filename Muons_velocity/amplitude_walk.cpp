/*
  c++ -o AWfit AWfit.cpp `root-config --glibs --cflags`
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "TProfile.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TProfile.h"


using namespace std ;
double funz(double * x, double * par){
    return par[0] + par[1] * log(x[0]/(x[0] - par[2] )) ;
  }


int main (int argc, char ** argv){

  double TDCdata, ADCdata1, ADCdata2, TDCdata_corrected;
  double m[] = {0.1221, 0.0008013}; //coefficiente angolare retta di calibrazione TDC
  double q[] = {0.8727, 0.3014}; //intercetta retta di calibrazione TDC
    
  vector<double> vx ;
  vector<double> vy ;
  vector<double> ex ;
  vector<double> ey ;

  gStyle->SetOptFit(1112);

  TF1 f ("f", funz, 0., 1000, 3) ;
  f.SetParameter (0, 31.5) ;
  f.SetParameter (1, 12.8) ;
  f.SetParameter (2, 18.) ;
  f.SetParName(0, "k");
  f.SetParName(1, "#tau");
  f.SetParName(2, "Vs");



  ifstream myfile;

//graph energy 1-----------------------------------------------------------------

  myfile.open("Data/data_tdcadc_38,2cm.txt");
  while(!myfile.eof()){
    myfile >> TDCdata;
    TDCdata_corrected = TDCdata*m[0] + q[0];
    if(TDCdata_corrected >= pow(10, -8)){ 
      vy.push_back (TDCdata_corrected);
      ey.push_back (0);
    }
    
    myfile >> ADCdata1;
    if(ADCdata1>=140 && ADCdata1<=300){ //38,2: 140 - 300 || 97,15 : 120 - 280
    vx.push_back (ADCdata1);
    ex.push_back (0);
    }  
    myfile >> ADCdata2;
    

  }
  myfile.close();

  //TGraphErrors g_funz1 (vx.size (), &vx[0], &vy[0], &ex[0], &ey[0]) ;
  
  TProfile *hprofile1 = new TProfile("hprof", "Profile", sqrt(vx.size()), 0, 2000);

  for (int i = 0; i < vx.size(); i++){
    hprofile1->Fill(vx.at(i), vy.at(i));
  }
  hprofile1->SetMarkerStyle(20);
  hprofile1->SetMarkerSize(0.3);

  //TFitResultPtr fit_result = g_funz.Fit (&f, "S") ;

  TFitResultPtr fit_profile1 = hprofile1->Fit(&f, "S");

  cout.precision (5) ;
  cout << "result of fit: " << fit_profile1->IsValid () << endl ;
  cout << "k : " << f.GetParameter (0) << "\t+- " << f.GetParError (0) << endl ;
  cout << "tau : " << f.GetParameter (1) << "\t+- " << f.GetParError (1) << endl ;

  hprofile1->SetMarkerStyle (4) ;


  hprofile1->SetTitle("tempi di volo Vs energy 1");
  hprofile1->GetXaxis()->SetTitle("ADC1");
  hprofile1->GetYaxis()->SetTitle("tempo[ns]");
  

  TCanvas c1 ("c1", "", 800, 800);
  hprofile1->Draw ("AP");
  c1.Print ("Graphs/AWfit_38,2cm_energy1 - TProfile.pdf", "pdf"); 

//clear vectors
  vx.clear();
  vy.clear();
  ex.clear();
  ey.clear();
  TDCdata = 0;
  ADCdata1 = 0;
  ADCdata2 = 0;

//graph energy 2-----------------------------------------------------------------
  
  myfile.open("Data/data_tdcadc_38,2cm.txt");
  while(!myfile.eof()){
    myfile >> TDCdata;
    TDCdata_corrected = TDCdata*m[0] + q[0];
    if(TDCdata_corrected >= pow(10, -8)){ 
    vy.push_back (TDCdata_corrected);
    ey.push_back (0);
    }

    myfile >> ADCdata1;
    myfile >> ADCdata2;
    if(ADCdata2>=120 && ADCdata2 <= 220){ //83,2: 120 - 220 || 97,15 : 100 - 200
      vx.push_back (ADCdata2) ;
      ex.push_back (0) ;
    }  
  }
  myfile.close();

  //TGraphErrors g_funz2 (vx.size (), &vx[0], &vy[0], &ex[0], &ey[0]) ;
  
  TProfile *hprofile2 = new TProfile("hprof", "Profile", sqrt(vx.size()), 0, 2000);

  for (int i = 0; i < vx.size(); i++){
    hprofile2->Fill(vx.at(i), vy.at(i));
  }

  //TFitResultPtr fit_result2 = g_funz2.Fit (&f, "S") ;

  TFitResultPtr fit_profile2 = hprofile2->Fit (&f, "S") ;

  cout.precision (5) ;
  cout << "result of fit: " << fit_profile2->IsValid () << endl ;
  cout << "k : " << f.GetParameter (0) << "\t+- " << f.GetParError (0) << endl ;
  cout << "tau : " << f.GetParameter (1) << "\t+- " << f.GetParError (1) << endl ;


  hprofile2->SetTitle("tempi di volo Vs energy 2");
  hprofile2->GetXaxis()->SetTitle("ADC2");
  hprofile2->GetYaxis()->SetTitle("tempo[ns]");
  

  TCanvas *c2 = new TCanvas();
  hprofile2->Draw();
  c2->Print("Graphs/AWfit_38,2cm_energy2 - TProfile.pdf", "pdf");

  return 0 ;
}