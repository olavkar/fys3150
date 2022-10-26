
#include <iostream>
#include <armadillo>

#ifndef __Particle_hpp__
#define __Particle_hpp__

class Particle{
public:

  double charge; // [e]
  double mass; // [u]
  arma::vec position; // [micrometer] (cubed in 3D?)
  arma::vec velocity; // [micrometer/microsecond] = [m/s] (cubed in 3D?)

  // Constructor for unspecified particle
  Particle();

  // Constructor for defined particle with charge, mass, position and velocity
  Particle(double charge_in, double mass_in, arma::vec position_in, arma::vec velocity_in);

};

#endif
