/*
	c++ -o medie_to_file calcola_medie.cpp `root-config --glibs --cflags`
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

double calcMean (const std::vector<double> & sample)
{
  double mean = 0. ;
  for (int i = 0 ; i < sample.size () ; ++i)
    mean += sample.at (i) ;
  return mean / sample.size () ;
}

double sum_vec(const std::vector<double> & sample){
  double sum = 0.;
  for (int i = 0; i < sample.size(); i++) {
    sum += sample.at(i);
  }
  return sum;
}

double calcVariance (const std::vector<double> & sample)
{
  double mean = 0. ;
  double meanSq = 0. ;
  for (int i = 0 ; i < sample.size () ; ++i)
    {
      mean += sample.at (i) ;
      meanSq += sample.at (i) * sample.at (i) ;
    }
  mean /= sample.size () ;
  return sample.size () * (meanSq / sample.size () - mean * mean) / (sample.size () - 1) ;
}

int main(int argc, char const *argv[]) {

  std::string filename = argv[1];
  std::ifstream dati;
  dati.open(filename, std::ios::in);
  std::vector<double> v_T1, v_T2;
  while (true) {
      double s1, s2;
      dati >> s1 >> s2;
      if(dati.eof()==true) break;
      v_T1.push_back(s1);
      v_T2.push_back(s2);
  }
	dati.close();

  double meanT1, meanT2, varT1, varT2;

  //meanT1 = calcMean(v_T1);
  varT1 = sqrt(calcVariance(v_T1)/v_T1.size());
  //meanT2 = calcMean(v_T2);
  varT2 = sqrt(calcVariance(v_T2)/v_T2.size());

  meanT1 = sum_vec(v_T1);
  meanT2 = sum_vec(v_T2);

  std::ofstream outfile_mean1("Data/means_detT1.txt", std::ios::app);
  if (outfile_mean1.is_open()) {
    outfile_mean1 << meanT1 << "\t" << varT1 << std::endl;
    outfile_mean1.close();
  }

  std::ofstream outfile_mean2("Data/means_detT2.txt", std::ios::app);
  if (outfile_mean2.is_open()) {
    outfile_mean2 << meanT2 << "\t" << varT2 << std::endl;
    outfile_mean2.close();
  }





  return 0;
}
