/*
	c++ -o analysis_efficiency analysis_efficiency.cpp `root-config --glibs --cflags`
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

//threshold of 800mV
  std::ifstream dati;
  dati.open("dati.txt", std::ios::in);

  std::vector<double> v_AlimetantionS1, v_AlimetantionS2, v_doublec, v_triplecS1, v_triplecS2, v_countsS1, v_countsS2;

  while (true) {
      double AlimetantionS1, AlimetantionS2, doublec, triplecS1, triplecS2, countsS1, countsS2;

      dati >> AlimetantionS1;
      dati >> AlimetantionS2;
      dati >> triplecS1;
      dati >> triplecS2;
      dati >> doublec;
      dati >> countsS1;
      dati >> countsS2;
      if(dati.eof()==true) break;
      v_AlimetantionS1.push_back(AlimetantionS1);
      std::cout<<AlimetantionS1<<std::endl;
      v_AlimetantionS2.push_back(AlimetantionS2);
      v_triplecS1.push_back(triplecS1);
      v_triplecS2.push_back(triplecS2);
      v_doublec.push_back(doublec);
      v_countsS1.push_back(countsS1);
      v_countsS2.push_back(countsS2);

  }
  dati.close();

  std::vector<double> v_efficiencyS1, v_efficiencyS2;

  for (int i = 0; i < v_countsS1.size(); i++) {
    v_efficiencyS1.push_back(v_triplecS1.at(i)/v_doublec.at(i));
    v_efficiencyS2.push_back(v_triplecS2.at(i)/v_doublec.at(i));
  }

  TGraphErrors g_S1, g_S2, g_countsS1, g_countsS2;
  for (int i = 0; i < v_efficiencyS1.size(); i++) {
    g_S1.SetPoint(i, v_AlimetantionS1.at(i), v_efficiencyS1.at(i));
    g_S1.SetPointError(i, 2., sqrt(v_doublec.at(i)*v_efficiencyS1.at(i)*(1-v_efficiencyS1.at(i))/v_doublec.at(i)));

    g_S2.SetPoint(i, v_AlimetantionS2.at(i), v_efficiencyS2.at(i));
    g_S2.SetPointError(i, 2., sqrt(v_doublec.at(i)*v_efficiencyS2.at(i)*(1-v_efficiencyS2.at(i))/v_doublec.at(i)));

    g_countsS1.SetPoint(i, v_AlimetantionS1.at(i), v_countsS1.at(i));
    g_countsS1.SetPointError(i, 2., sqrt(v_countsS1.at(i)));

    g_countsS2.SetPoint(i, v_AlimetantionS2.at(i), v_countsS2.at(i));
    g_countsS2.SetPointError(i, 2., sqrt(v_countsS2.at(i)));
  }

  for (int i = 0; i < v_efficiencyS1.size(); i++) {
    std::cout << sqrt(v_triplecS1.at(i)*v_efficiencyS1.at(i)*(1-v_efficiencyS1.at(i))) << '\n';
  }

  g_S1.RemovePoint(10);

  g_S1.SetMarkerStyle(21);
  g_S1.SetMarkerSize(1.5);
  g_S2.SetMarkerStyle(21);
  g_S2.SetMarkerSize(1.5);

  g_countsS1.SetMarkerStyle(21);
  g_countsS1.SetMarkerSize(1.5);
  g_countsS2.SetMarkerStyle(21);
  g_countsS2.SetMarkerSize(1.5);


  TCanvas c1;
  c1.cd(1);
  c1.SetGridx();
  c1.SetGridy();
  c1.SetLeftMargin(.17);
  c1.SetBottomMargin(.17);

  c1.SetWindowSize (1150, 900);
  g_S1.GetHistogram()->GetXaxis()->SetTitleSize(0.07);
  g_S1.GetHistogram()->GetYaxis()->SetTitleSize(0.05);
  g_S1.GetHistogram()->GetXaxis()->SetLabelOffset(0.005);
  g_S1.GetHistogram()->GetYaxis()->SetLabelOffset(0.001);

  g_S1.SetTitle("; V_{alimentazione} [V]; efficienza");
  //g_S1.GetHistogram()->GetYaxis()->SetRangeUser(0., 505.);
  //g_S1.GetHistogram()->GetXaxis()->SetRangeUser(0., 1.12);
  g_S1.Draw("AP");
  c1.Print("Graphs/efficiencyS1.pdf", "pdf");


  TCanvas c2;
  c2.cd(2);
  c2.SetGridx();
  c2.SetGridy();
  c2.SetLeftMargin(.17);
  c2.SetBottomMargin(.17);

  c2.SetWindowSize (1150, 900);
  g_S2.GetHistogram()->GetXaxis()->SetTitleSize(0.07);
  g_S2.GetHistogram()->GetYaxis()->SetTitleSize(0.05);
  g_S2.GetHistogram()->GetXaxis()->SetLabelOffset(0.005);
  g_S2.GetHistogram()->GetYaxis()->SetLabelOffset(0.001);

  g_S2.SetTitle("; V_{alimentazione} [V]; efficienza");
  //g_S2.GetHistogram()->GetYaxis()->SetRangeUser(0., 505.);
  //g_S2.GetHistogram()->GetXaxis()->SetRangeUser(0., 1.12);
  g_S2.Draw("AP");

  c2.Print("Graphs/efficiencyS2.pdf", "pdf");


  TCanvas c3;
  c3.cd(3);
  c3.SetGridx();
  c3.SetGridy();
  c3.SetLeftMargin(.17);
  c3.SetBottomMargin(.17);

  c3.SetWindowSize (1150, 900);
  g_countsS1.GetHistogram()->GetXaxis()->SetRangeUser(800., 1500.);
  g_countsS1.GetHistogram()->GetYaxis()->SetRangeUser(0., 450000.);
  g_countsS1.GetHistogram()->GetXaxis()->SetTitleSize(0.065);
  g_countsS1.GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  g_countsS1.GetHistogram()->GetXaxis()->SetLabelOffset(0.005);
  g_countsS1.GetHistogram()->GetYaxis()->SetLabelOffset(0.001);

  g_countsS1.SetTitle(" ; V_{alimentazione} [V]; #frac{Conteggi}{Minuto} #left[#frac{1}{min}#right]");
  //g_S2.GetHistogram()->GetYaxis()->SetRangeUser(0., 505.);
  //g_S2.GetHistogram()->GetXaxis()->SetRangeUser(0., 1.12);
  g_countsS1.Draw("AP");
  c3.Print("Graphs/countsS1.pdf", "pdf");


  TCanvas c4;
  c4.cd(4);
  c4.SetGridx();
  c4.SetGridy();
  c4.SetLeftMargin(.17);
  c4.SetBottomMargin(.17);

  c4.SetWindowSize (1150, 900);
  g_countsS2.GetHistogram()->GetXaxis()->SetRangeUser(800., 1500.);
  g_countsS2.GetHistogram()->GetYaxis()->SetRangeUser(0., 450000.);
  g_countsS2.GetHistogram()->GetXaxis()->SetTitleSize(0.065);
  g_countsS2.GetHistogram()->GetYaxis()->SetTitleSize(0.045);
  g_countsS2.GetHistogram()->GetXaxis()->SetLabelOffset(0.005);
  g_countsS2.GetHistogram()->GetYaxis()->SetLabelOffset(0.001);


  g_countsS2.SetTitle(" ; V_{alimentazione} [V]; #frac{Conteggi}{Minuto} #left[#frac{1}{min}#right]");
  //g_S2.GetHistogram()->GetYaxis()->SetRangeUser(0., 505.);
  //g_S2.GetHistogram()->GetXaxis()->SetRangeUser(0., 1.12);
  g_countsS2.Draw("AP");
  c4.Print("Graphs/countsS2.pdf", "pdf");


  theApp.Run();

  return 0;
}
