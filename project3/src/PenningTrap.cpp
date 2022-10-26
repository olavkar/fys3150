
#include "PenningTrap.hpp"

PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, bool coloumb_interactions_in, double time_in, bool time_dep_in, double f_in, double omega_V_in){
  ke = 1.38935333*pow(10, 5);
  time = time_in;
  time_dep = time_dep_in;
  coloumb_interactions = coloumb_interactions_in;

  B0 = B0_in;
  V0 = V0_in;
  d = d_in;
  f = f_in;
  omega_V = omega_V_in;
  V0_d2 = V0/pow(d, 2);
}

void PenningTrap::add_particles(std::vector<Particle> particles_in){
  // Method inspired (copied) from https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector (17-10-22)
  particles.insert(particles.end(), particles_in.begin(), particles_in.end());

  x0 = particles[0].position(0);
  z0 = particles[0].position(2);
  v0 = particles[0].velocity(1);
}

void PenningTrap::add_random(int n, int charge, double mass){
  arma::arma_rng::set_seed_random();
  std::vector<Particle> random_particles;
  for (int i = 0; i < n; i++){
    arma::vec r = arma::vec(3).randn()*0.1*d;
    arma::vec v = arma::vec(3).randn()*0.1*d;
    Particle p = Particle(charge, mass, r, v);
    random_particles.push_back(p);

  }
  PenningTrap::add_particles(random_particles);
}

arma::vec PenningTrap::electric_field(arma::vec r){
  // Defines vector E and makes the elements the gradient of V
  arma::vec E = arma::vec(3).fill(0);
  double V0_d2_ = V0_d2;
  if (time_dep){
    V0_d2_ = V0*(1. + f*cos(omega_V*(2.*M_PI)*time))/pow(d, 2.);
  }
  if (std::sqrt(r(0)*r(0) + r(1)*r(1) + r(2)*r(2)) < d){
    E(0) = V0_d2_*r(0);
    E(1) = V0_d2_*r(1);
    E(2) = -2*V0_d2_*r(2);
  }
  return E;
}

arma::vec PenningTrap::magnetic_field(arma::vec r){
  // Defines vector B and makes the z-element B0
  arma::vec B = arma::vec(3).fill(0);
  if (std::sqrt(r(0)*r(0) + r(1)*r(1) + r(2)*r(2)) < d){
    B(2) = B0;
  }
  return B;
}

arma::vec PenningTrap::particle_E_fields(int i){
  // Defines vector E and sums over all non-i particle force contributions
  arma::vec E = arma::vec(3).fill(0);

  if (coloumb_interactions){
    int n_particles = particles.size();
    if (n_particles == 1){
      throw std::invalid_argument("zero particles cant interact with i");
    }

    Particle p_i = particles[i];
    for (int j = 0; j < n_particles; j++){
      if (j != i){
        Particle p_j = particles[j];
        arma::vec r = p_i.position - p_j.position;
        double abs_r = std::sqrt(r(0)*r(0) + r(1)*r(1) + r(2)*r(2));
        E += p_j.charge*r/pow(abs_r, 3);
      }
    }
  }

  return E*ke; // <-- this is the electric field
}

void PenningTrap::forward_Euler(double h){
  int n_particles = particles.size();
  std::vector<Particle> new_particles = particles; // 'save' current positions and velocites

  for (int i = 0; i < n_particles; i++){
    Particle& p_i = new_particles[i];
    double temp = h*p_i.charge/p_i.mass;

    p_i.velocity += temp*(PenningTrap::electric_field(p_i.position) + arma::cross(p_i.velocity, PenningTrap::magnetic_field(p_i.position))); // external electric and magnetic force

    if (n_particles > 1){
      p_i.velocity += temp*PenningTrap::particle_E_fields(i); // inter-particle electric force
    }

    p_i.position += h*particles[i].velocity; // old velocity
  }

  particles = new_particles;
  time += h;
}

void PenningTrap::Runge_Kutta4(double h){
  int n_particles = particles.size();
  std::vector<Particle> old_particles = particles;

  // calculating k1 for all partficles
  arma::mat k1v = arma::mat(3, n_particles);
  arma::mat k1r = arma::mat(3, n_particles);
  for (int i = 0; i < n_particles; i++){
    Particle p_i = particles[i];
    double temp = h*p_i.charge/p_i.mass;

    k1v.col(i) = temp*(PenningTrap::electric_field(p_i.position) + arma::cross(p_i.velocity, PenningTrap::magnetic_field(p_i.position)));
    if (n_particles > 1 && coloumb_interactions){
      k1v.col(i) += temp*PenningTrap::particle_E_fields(i);
    }

    k1r.col(i) = h*p_i.velocity;

    // prepping k2
    particles[i].velocity += 0.5*k1v.col(i);
    particles[i].position += 0.5*k1r.col(i);
  }

  // calculating k2 for all particles
  arma::mat k2v = arma::mat(3, n_particles);
  arma::mat k2r = arma::mat(3, n_particles);
  for (int i = 0; i < n_particles; i++){
    Particle p_i = particles[i];
    double temp = h*p_i.charge/p_i.mass;

    k2v.col(i) = temp*(PenningTrap::electric_field(p_i.position) + arma::cross(p_i.velocity, PenningTrap::magnetic_field(p_i.position)));
    if (n_particles > 1 && coloumb_interactions){
      k2v.col(i) += temp*PenningTrap::particle_E_fields(i);
    }

    k2r.col(i) = h*particles[i].velocity;

    // prepping k3
    particles = old_particles;
    particles[i].velocity += 0.5*k2v.col(i);
    particles[i].position += 0.5*k2r.col(i);
  }

  // calculating k3
  arma::mat k3v = arma::mat(3, n_particles);
  arma::mat k3r = arma::mat(3, n_particles);
  for (int i = 0; i < n_particles; i++){
    Particle p_i = particles[i];
    double temp = h*p_i.charge/p_i.mass;

    k3v.col(i) = temp*(PenningTrap::electric_field(p_i.position) + arma::cross(p_i.velocity, PenningTrap::magnetic_field(p_i.position)));
    if (n_particles > 1 && coloumb_interactions){
      k3v.col(i) += temp*PenningTrap::particle_E_fields(i);
    }

    k3r.col(i) = h*particles[i].velocity;

    // prepping k4
    particles = old_particles;
    particles[i].velocity += k3v.col(i);
    particles[i].position += k3r.col(i);
  }

  // calculating k4
  arma::mat k4v = arma::mat(3, n_particles);
  arma::mat k4r = arma::mat(3, n_particles);
  for (int i = 0; i < n_particles; i++){
    Particle p_i = particles[i];
    double temp = h*p_i.charge/p_i.mass;

    k4v.col(i) = temp*(PenningTrap::electric_field(p_i.position) + arma::cross(p_i.velocity, PenningTrap::magnetic_field(p_i.position)));
    if (n_particles > 1 && coloumb_interactions){
      k4v.col(i) += temp*PenningTrap::particle_E_fields(i);
    }

    k4r.col(i) = h*particles[i].velocity;
  }

  // calculating next step
  for (int i = 0; i < n_particles; i++){
    old_particles[i].velocity += 1./6.*(k1v.col(i) + 2*k2v.col(i) + 2*k3v.col(i) + k4v.col(i));
    old_particles[i].position += 1./6.*(k1r.col(i) + 2*k2r.col(i) + 2*k3r.col(i) + k4r.col(i));
  }
  particles = old_particles;
  time += h;
}

void PenningTrap::analytical_evolution(double h){
  time += h;
  
  if (particles.size() > 1){
    throw std::invalid_argument("analytical solution is only valid for ONE particle");
  }
  if (time_dep){
    throw std::invalid_argument("fields have to be static"); // not really gonna matter, this one
  }

  double omega_0 = particles[0].charge*B0/particles[0].mass;
  double omega_z2 = 2.*particles[0].charge*V0_d2/particles[0].mass;

  double omega_p = (omega_0 + std::sqrt(pow(omega_0, 2) - 2*omega_z2))/2.;
  double omega_m = (omega_0 - std::sqrt(pow(omega_0, 2) - 2*omega_z2))/2.;

  double A_p = (v0 + omega_m*x0)/(omega_m-omega_p);
  double A_m = -(v0 + omega_p*x0)/(omega_m-omega_p);

  std::complex<double> i(0, 1);

  double x = std::real(A_p*std::exp(-i*omega_p*time) + A_m*std::exp(-i*omega_m*time));
  double y = std::imag(A_p*std::exp(-i*omega_p*time) + A_m*std::exp(-i*omega_m*time));
  double z = z0*cos(std::sqrt(omega_z2)*time);

  particles[0].position(0) = x;
  particles[0].position(1) = y;
  particles[0].position(2) = z;
}

int PenningTrap::count_particles(){
  int n_particles = particles.size();
  int n = 0;

  for (int i = 0; i < n_particles; i++){
    arma::vec r = particles[i].position;
    double abs_r = std::sqrt(r(0)*r(0) + r(1)*r(1) + r(2)*r(2));
    if (abs_r < d){
      n += 1;
    }
  }

  return n;
}
