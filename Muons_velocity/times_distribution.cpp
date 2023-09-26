/*
c++ -o distribution_times distribution_times.cpp `root-config --glibs --cflags`
./distribution_times 9.5cm
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
#include "TH1F.h"
#include "TAxis.h"
#include "TFitResult.h"

#define NEV 80000

using namespace std;
int main(int argc, char* argv[]){

//distribution of the times of fly for every distance L    
    TH1F distribution_times_cut_excess ("9.5 cm", "  ", sqrt(NEV), 1., 500.); // name, n bin, min, max
    
    TApplication theApp("theApp", &argc, argv);


    ifstream data_cut_excess;
	string fileData = "Data/data_tdcadc_";
    string lenght = argv[1];
    string extension = ".txt";
    data_cut_excess.open((fileData+lenght+extension).c_str(), ios::in);
    double TDCdata, ADCdata1, ADCdata2;
    double cutSupADC1, cutInfADC1, cutInfADC2, cutSupADC2;

    double m[] = {0.1221, 0.0008013}; // angular coefficient line of calibration TDC
    double q[] = {0.8727, 0.3014};    // offset line of calibration TDC


    if(stod(argv[1]) == 9.5){
        cutInfADC1 = 140; //-->-0.4canali (-->  -0.6)
        cutSupADC1 = 340;
        cutInfADC2 = 80;
        cutSupADC2 = 280;
    }
    if(stod(argv[1]) == 38.2){
        cutInfADC1 = 100; //-->-0.1canali (--> -0.1)
        cutSupADC1 = 360;
        cutInfADC2 = 80;
        cutSupADC2 = 280;
      }
    if(stod(argv[1]) == 97.15){
        cutInfADC1 = 80; //-->+0.1canali (--> +0.6)
        cutSupADC1 = 360;
        cutInfADC2 = 80;
        cutSupADC2 = 260;
    }
    if(stod(argv[1]) == 171.5){
        cutInfADC1 = 80; //--> 40 canali a dx e a sx --> -0.4canali (-->60 canali a dx e a sx-->-2.3 canali)
        cutSupADC1 = 360;
        cutInfADC2 = 40;
        cutSupADC2 = 240;
    }


    while(!data_cut_excess.eof()){
        data_cut_excess >> TDCdata;
        data_cut_excess >> ADCdata1;
        data_cut_excess >> ADCdata2;
        if (ADCdata1 >= cutInfADC1 && ADCdata1 <= cutSupADC1 && ADCdata2 >= cutInfADC2 && ADCdata2 <= cutSupADC2){
            distribution_times_cut_excess.Fill(TDCdata);
        } 
    }
    data_cut_excess.close();
    

    TCanvas c1 ("c1", "", 800, 800);

    c1.SetLeftMargin(.17);
    c1.SetBottomMargin(.17);
    
    distribution_times_cut_excess.GetXaxis()->SetTitle("TDC [canali]");
    distribution_times_cut_excess.GetYaxis()->SetTitle("conteggi");
    distribution_times_cut_excess.GetXaxis()->SetTitleSize(0.055);
    distribution_times_cut_excess.GetYaxis()->SetTitleSize(0.055);
    distribution_times_cut_excess.GetXaxis()->SetLabelSize(0.035);
    distribution_times_cut_excess.GetYaxis()->SetLabelSize(0.035);


    distribution_times_cut_excess.SetFillColor (kOrange + 2) ;
    distribution_times_cut_excess.Draw ();
    string fileGraphs = "Graphs/distribution_times_cut_excess";
    string extensionPDF = ".pdf";

 //   c1.Print((fileGraphs+lenght+extensionPDF).c_str(), "pdf");

//distribution of the times of fly for every distance L    
    TH1F distribution_times_cut_right ("9.5 cm", "  ", sqrt(NEV), 1., 500.); // name, n bin, min, max

    ifstream data_cut;
    data_cut.open((fileData+lenght+extension).c_str(), ios::in);


    if(stod(argv[1]) == 9.5){
        cutInfADC1 = 180;
        cutSupADC1 = 300;
        cutInfADC2 = 120;
        cutSupADC2 = 240;
    }
    if(stod(argv[1]) == 38.2){
        cutInfADC1 = 140;
        cutSupADC1 = 320;
        cutInfADC2 = 120;
        cutSupADC2 = 240;
      }
    if(stod(argv[1]) == 97.15){
        cutInfADC1 = 120;
        cutSupADC1 = 320;
        cutInfADC2 = 80;
        cutSupADC2 = 200;
    }
    if(stod(argv[1]) == 171.5){
        cutInfADC1 = 120;
        cutSupADC1 = 320;
        cutInfADC2 = 80;
        cutSupADC2 = 200;
    }

    while(!data_cut.eof()){

        data_cut >> TDCdata;
        data_cut >> ADCdata1;
        data_cut >> ADCdata2;
        if (ADCdata1 >= cutInfADC1 && ADCdata1 <= cutSupADC1 && ADCdata2 >= cutInfADC2 && ADCdata2 <= cutSupADC2){
            distribution_times_cut_right.Fill(TDCdata);
        }
    }
    data_cut.close();

    TCanvas c2 ("c2", "", 800, 800);

    c2.SetLeftMargin(.17);
    c2.SetBottomMargin(.17);
    
    distribution_times_cut_right.GetXaxis()->SetTitle("TDC [canali]");
    distribution_times_cut_right.GetYaxis()->SetTitle("conteggi");
    distribution_times_cut_right.GetXaxis()->SetTitleSize(0.055);
    distribution_times_cut_right.GetYaxis()->SetTitleSize(0.055);
    distribution_times_cut_right.GetXaxis()->SetLabelSize(0.035);
    distribution_times_cut_right.GetYaxis()->SetLabelSize(0.035);



    distribution_times_cut_right.SetFillColor (kOrange + 2) ;
    distribution_times_cut_right.Draw ();
    string fileGraphsCut = "Graphs/distribution_times_cut_";
    c2.Print((fileGraphsCut+lenght+extensionPDF).c_str(), "pdf");
    theApp.Run();
    return 0;
}
