/*
	c++ -o plottiamo_dx plottiamo_destra.cpp `root-config --glibs --cflags`
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
  data.open("Data/means_detT2.txt", std::ios::in);
  std::vector<double> v_mean, v_sigma;
  while (true) {
      double mean, sigma;
      data >> mean >> sigma;
      if(data.eof()==true) break;
      v_mean.push_back(mean);
      v_sigma.push_back(sigma);
  }
  data.close();
//794	1.05344
  std::ifstream threshold;
  threshold.open("Data/thresholds_detT2.txt", std::ios::in);
  std::vector<double> v_thresholds1, v_thresholds2, v_freq, v_time;
  while (true) {
      double threshold1, threshold2;
      int freq, time;
      threshold >> threshold1 >> threshold2 >> freq >> time;
      if(threshold.eof()==true) break;
      v_thresholds1.push_back(threshold1);
      v_thresholds2.push_back(threshold2);
      v_freq.push_back(freq);
      v_time.push_back(time);
  }
  threshold.close();


  TGraphErrors g1;
  for (int i = 0; i < v_mean.size()-5; i++) {
    g1.SetPoint(i, v_thresholds1.at(i), v_mean.at(i)/v_time.at(i));
  }

  for (int i = 0; i < v_sigma.size()-5; i++) {
    g1.SetPointError(i, 0.001, sqrt(v_mean.at(i))/v_time.at(i)); //distribuzione poissoniana -> sigma=rad(n)
  }


  g1.SetMarkerStyle(20);
  g1.SetMarkerSize(0.7);

  g1.SetTitle("Rate vs Soglia");
  g1.GetHistogram()-> GetXaxis()->SetTitle("V_{soglia}");
  //g1.GetHistogram()->GetYaxis()->SetRangeUser(-5., 600.);
  g1.GetHistogram()-> GetYaxis()->SetTitle("Conteggi/Minuto");


  double rangeX_1, rangeX_2;
  int k = 0;
  rangeX_1 = .410;
  rangeX_2 = .509;


 TGraph g_fill1, g_fill2;
  for(int j = 60.; j<rangeX_1*200.; j++){
    for (int i = 0; i < 500; i+=5) {
      g_fill1.SetPoint(k, j/200., i);
      k++;
    }
  }

  k = 0;
  for(int j = rangeX_2*200.; j<=240.; j++){
    for (int i = 0; i < 500; i+=5) {
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

  multi.SetTitle("; V_{threshold} [V]; #frac{Conteggi}{Minuto} #left[#frac{1}{Minuto}#right]");
  multi.GetHistogram()->GetYaxis()->SetRangeUser(0., 505.);
  multi.GetHistogram()->GetXaxis()->SetRangeUser(0., 1.12);
  multi.GetHistogram()->GetXaxis()->SetTitleSize(0.045);
  multi.GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  multi.Draw("AP");


  c1.Print("threshold_graph_detT2.pdf", "pdf");
  theApp.Run();


  return 0;
}
