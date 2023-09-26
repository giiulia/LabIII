/*
	c++ -o plottiamo_sx plottiamo_sinistra.cpp `root-config --glibs --cflags`
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TAttFill.h"
#include "TMultiGraph.h"
#include "TStyle.h"

int main(int argc, char **argv) {
  TApplication theApp("theApp", &argc, argv);
  gStyle->SetOptFit(1112);

  std::ifstream data;
  data.open("Data/means_detT1.txt", std::ios::in);
  std::vector<double> v_mean, v_thresholds;// v_sigma;
  while (true) {
      double threshlod, mean1, mean2;// sigma;
      data >> threshlod >> mean1 >> mean2;// >> sigma;
      if(data.eof()==true) break;
      v_thresholds.push_back(threshlod);
      v_mean.push_back((mean1+mean2)/2);
      //v_sigma.push_back(sigma);
  }
  data.close();

  TGraphErrors g1;
  for (int i = 0; i < v_mean.size(); i++) {
    g1.SetPoint(i, v_thresholds.at(i), v_mean.at(i));
  }
  for (int i = 0; i < v_mean.size(); i++) {
    g1.SetPointError(i, 0.001, sqrt(48));
  }

  g1.SetMarkerStyle(20);
  g1.SetMarkerSize(0.7);

  double rangeX_1, rangeX_2;
  int k = 0;
  rangeX_1 = .400;
  rangeX_2 = .510;


  TGraph g_fill1, g_fill2;
  for(int j = 68.; j<rangeX_1*200.; j++){
    for (int i = 0; i < 350; i+=3) {
      g_fill1.SetPoint(k, j/200., i);
      k++;
    }
  }

  k = 0;
  for(int j = rangeX_2*200.; j<=160.; j++){
    for (int i = 0; i < 350; i+=3) {
      g_fill2.SetPoint(k, j/200., i);
      k++;
    }
  }
  g_fill1.SetFillStyle(3004);
  g_fill1.SetMarkerStyle(20);
  g_fill1.SetMarkerColor(33);
  g_fill1.SetMarkerSize(0.75);

  g_fill2.SetFillStyle(3004);
  g_fill2.SetMarkerStyle(20);
  g_fill2.SetMarkerColor(33);
  g_fill2.SetMarkerSize(0.75);


  TMultiGraph multi;
  multi.Add(&g_fill1);
  multi.Add(&g_fill2);
  multi.Add(&g1);

  TCanvas c1;
  c1.SetGridx ();
  c1.SetGridy ();
  c1.SetLeftMargin(.15);
  c1.SetWindowSize (1050, 900);

  multi.SetTitle("; V_{soglia} [V]; #frac{Conteggi}{Minuto} #left[#frac{1}{Minuto}#right]");
  multi.GetHistogram()->GetYaxis()->SetRangeUser(0., 350.);
  multi.GetHistogram()->GetXaxis()->SetRangeUser(0., 0.82);
  multi.GetHistogram()->GetXaxis()->SetTitleSize(0.045);
  multi.GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  multi.Draw("AP");

  c1.Print("threshold_graph_detT1.pdf", "pdf");
  theApp.Run();


  return 0;
}
