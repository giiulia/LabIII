  /*
	c++ -o coincidences coincidences.cpp `root-config --glibs --cflags`
  tra S1 e S2 not retarded there is a delay of 1.6ns
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
#include "TLatex.h"
#include "TAttFill.h"
#include "TMultiGraph.h"
#include "TStyle.h"

using namespace std;
int main(int argc, char **argv) {
  TApplication theApp("theApp", &argc, argv);
  gStyle->SetOptFit(1112);

  ifstream data;
  data.open("Data/g1.txt", ios::in);
  vector<double> v_delay, v_counts;
  while (true) {
      double delay, counts;
      data >> delay >> counts;
      if(data.eof()==true) break;

      v_delay.push_back(delay-1.6);
      v_counts.push_back(counts/5); //measures taken in 5 minutes
  }
  data.close();

  ifstream data2;
  data2.open("Data/g2.txt", std::ios::in);
  std::vector<double> v_delay2, v_counts2;
  while (true) {
      double delay2, counts2;
      data2 >> delay2 >> counts2;
      if(data2.eof()==true) break;
      v_delay2.push_back(delay2-1.6);
      v_counts2.push_back(counts2/5); //measures taken in 5 minutes
  }
  data2.close();

  ifstream data3;
  data3.open("Data/g3.txt", std::ios::in);
  std::vector<double> v_delay3, v_counts3;
  while (true) {
      double delay3, counts3;
      data3 >> delay3 >> counts3;
      if(data3.eof()==true) break;
      v_delay3.push_back(delay3-1.6);
      v_counts3.push_back(counts3/5); //measures taken in 5 minutes
  }
  data3.close();



  TGraphErrors g1, g2, g3;
  for (int i = 0; i < v_counts.size(); i++) {
    g1.SetPoint(i, v_delay.at(i), v_counts.at(i));
    g1.SetPointError(i, 0.4, sqrt(v_counts.at(i)));
  }

  for (int i = 0; i < v_counts2.size(); i++) {
    g2.SetPoint(i, v_delay2.at(i), v_counts2.at(i));
    g2.SetPointError(i, 0.4, sqrt(v_counts2.at(i)));
  }

  for (int i = 0; i < v_counts3.size(); i++) { //data ignored
    g3.SetPoint(i, v_delay3.at(i), v_counts3.at(i));
    g3.SetPointError(i, 0.4, sqrt(v_counts3.at(i)));
  }

  g1.SetMarkerStyle(20);
  g1.SetMarkerSize(0.5);

  g2.SetMarkerStyle(20);
  g2.SetMarkerSize(0.5);

  g3.SetMarkerStyle(20);
  g3.SetMarkerSize(0.5);


  double accidental_coinc;

/*
  TF1 model("model", "gaus");
  TFitResultPtr fit_result = g2.Fit(&model, "S");

  double sigma = model.GetParameter(2);
  double resolving_time_ns = sigma/2;
  cout << " resolving time accordig to the bell fit = " << resolving_time_ns << " ns" << endl;
*/
  //from data.txt of Efficiency, counts/min associated with chosen tensions of Alimentation 
  double rA = 229165;
  double rB = 213969;

  cout << " 1/rA = " << 1/rA << " 1/rB = " << 1/rB <<endl;

  //accidental_coinc = (1-exp(-rB*(2*resolving_time_sec)))*rA+(1-exp(-rA*(2*resolving_time_sec)))*rB; //formula more precise, not needed
  accidental_coinc = rA*rB*24.68*pow(10, -9)/60; //width of the 2 signals put toegether measured with oscilloscope = 24.68 +- 0.4 ns

  std::cout << "number of accidental coincidences in theory = " << accidental_coinc <<  " 1/min" << "\n";


  TF1 line("line", "[0]");
  TFitResultPtr fit_result2 = g1.Fit(&line, "S");
  //line.SetParName(0, "m");
  line.SetParName(0, "q");
  //line.SetParameter(0, 1.);

  TMultiGraph multi;

  multi.Add(&g1);
  multi.Add(&g2);
  multi.Add(&g3);


  TCanvas c1;
  c1.SetLeftMargin(.18);
  c1.SetBottomMargin(.18);
  multi.SetTitle(" ; Ritardo [ns]; #frac{Conteggi}{Minuto} #left[#frac{1}{min}#right]");
  multi.GetHistogram()->GetXaxis()->SetTitleSize(0.055);
  multi.GetHistogram()->GetYaxis()->SetTitleSize(0.055);
  multi.GetHistogram()->GetXaxis()->SetLabelSize(0.05);
  multi.GetHistogram()->GetYaxis()->SetLabelSize(0.05);

  multi.Draw("AP");
  theApp.Run();


  return 0;
}
