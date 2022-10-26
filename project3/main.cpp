
#include "Particle.hpp"
#include "PenningTrap.hpp"

int main(){
  // constants
  double B0 = 9.65*10;
  double V0 = 2.41*pow(10, 6);
  double d = 500.;
  double V0_d2 = V0/pow(d, 2);
  double omega_V = 0.2;

  Particle p1 = Particle(1., 40.078, {20., 0., 20.}, {0., 25., 0.});
  Particle p2 = Particle(1., 40.078, {25., 25., 0.}, {0., 40., 5.});

  PenningTrap penning_trap = PenningTrap(B0, V0, d, false, 0., false, 0.1, omega_V);
  PenningTrap penning_anal = PenningTrap(B0, V0, d, true, 0., false, 1., 250000.);
  penning_trap.add_particles({p1});
  penning_anal.add_particles({p1});
  //penning_anal.add_particles({p1});

  double time = 50.;
  int n = 8000.;
  double h = time/n;

  std::cout << penning_trap.particles[0].position(0) << " " <<penning_trap.particles[0].position(1) << " " << penning_trap.particles[0].position(2);
  std::cout << " " << penning_anal.particles[0].position(0) << " " <<penning_anal.particles[0].position(1) << " " << penning_anal.particles[0].position(2);
  std::cout << " " << penning_trap.time << std::endl;

  for (int i = 0; i < n; i++){
    penning_trap.Runge_Kutta4(h);
    penning_anal.analytical_evolution(h);
    std::cout << penning_trap.particles[0].position(0) << " " <<penning_trap.particles[0].position(1) << " " << penning_trap.particles[0].position(2);
    std::cout << " " << penning_anal.particles[0].position(0) << " " <<penning_anal.particles[0].position(1) << " " << penning_anal.particles[0].position(2);
    std::cout << " " << penning_trap.time << std::endl;
  }
  return 0;
}
