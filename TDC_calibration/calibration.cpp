/*
	c++ -o main main.cpp `root-config --glibs --cflags`

  error on time 0.4
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
  data.open("Data/calibration_data_TDC.txt", std::ios::in);
  std::vector<double> v_time, v_tdc;
  while (true) {
      double time, tdc;
      data >> time;
      data >> tdc;
      if(data.eof()==true) break;
      v_time.push_back(time+5);
      v_tdc.push_back(tdc);
  }
  data.close();

  TGraphErrors g1;

  for (int i = 0; i < v_time.size(); i++) {
    g1.SetPoint(i, v_tdc.at(i), v_time.at(i));
    g1.SetPointError(i, 1.,  0.4);
  }

  g1.SetMarkerStyle(20);
  g1.SetMarkerSize(0.3);
  g1.GetHistogram()->GetXaxis()->SetTitleSize(0.06);
  g1.GetHistogram()->GetYaxis()->SetTitleSize(0.06);


  TF1 model("model", "[0]*x+[1]");
  model.SetParName(0, "m");
  model.SetParName(1, "q");

  TFitResultPtr fit_result = g1.Fit(&model, "S");

  TCanvas c1;

  c1.SetLeftMargin(.15);
  c1.SetBottomMargin(.15);
  
  g1.SetTitle(" ; TDC [canali]; Tempo [ns]");
  g1.GetHistogram()->GetXaxis()->SetLabelSize(0.06);
  g1.GetHistogram()->GetYaxis()->SetLabelSize(0.06);
  g1.Draw("AP");
  theApp.Run();

  return 0;
}
