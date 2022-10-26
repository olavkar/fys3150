
#include <vector>
#include <cmath>
#include <math.h>

#include "Particle.hpp"

#ifndef __PenningTrap_hpp__
#define __PenningTrap_hpp__

class PenningTrap{
public:

  double ke; // Coulumb constant [u*micrometer^3/(microsecond^2*e^2)]
  double time; // current time in Penning trap
  bool time_dep; // time-dependant electric field
  bool coloumb_interactions; // whether coloumb interactions between particles is on or off

  double B0; // Magnetic field strength [u/(microsecond*e)]
  double V0; // Applied potential [u*micrometer^2/(microsecond^2*e)]
  double d; // Characteristic dimension [micrometer]
  double V0_d2; // Ratio V0 over d^2
  std::vector<Particle> particles;
  double f; // time-dependant electric field amplitude
  double omega_V; // time-dependant electric field frequency

  // used for analytical solution
  double x0; // initial position along x-axis
  double z0; // initial position along z-axis
  double v0; // initial velocity in y-direction

  // Constructor for empty Penning trap
  PenningTrap(double B0_in, double V0_in, double d_in, bool coloumb_interactions_in = true, double time_in = 0, bool time_dep_in = false, double f_in = 1, double omega_V_in = 1);

  // Adds the particels from a vector to the Penning trap
  void add_particles(std::vector<Particle> particles_in);

  // Adds n particles with random starting positions and velocites
  void add_random(int n, int charge = 1, double mass = 40.078);

  // Evaluates the external electric field in position r
  arma::vec electric_field(arma::vec r);

  // Evaluates the external magnetic field in position r
  arma::vec magnetic_field(arma::vec r);

  // Evaluates the electric fields from other particles in particle i
  arma::vec particle_E_fields(int i);

  // Run one time step h using Forward Euler numerical method
  void forward_Euler(double h);

  // Run one time step h using Runge Kutta 4th order numerical method
  void Runge_Kutta4(double h);

  // Run one time step h using the analytical solution for one particle in static fields
  void analytical_evolution(double h);

  // count number of particles within a sphere of radius d of the origin at current time
  int count_particles();

};

#endif
