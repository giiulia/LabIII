#include "muon_class.h"
#include <math.h>
#include <vector>

#define _USE_MATH_DEFINES

Muon::Muon(double theta, double phi):
  ang_theta(theta),
  ang_phi(phi)
  {}

Muon::~Muon(){
}

double Muon::get_theta(){
  return ang_theta;
}

double Muon::get_phi(){
  return ang_phi;
}

double Muon::coeff_x(){
  return tan(ang_theta)*cos(ang_phi);
}

double Muon::coeff_y(){
  return tan(ang_theta)*sin(ang_phi);
}
