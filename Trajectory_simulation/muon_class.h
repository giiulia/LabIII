#include <vector>

class Muon{
public:
  
  Muon(double theta, double phi);
  
  ~Muon ();

  double coeff_x();
  double coeff_y();

  double get_theta();
  double get_phi();

private:
  double ang_theta;
  double ang_phi;

};
