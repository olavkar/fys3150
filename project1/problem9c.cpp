// Problem 9c

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

// Declerations
double g_func(double x, double h);

// Main
int main(){
  // defining vectors
  int n = 1000; // number of non-end points
  double h = 1./(n+1); // step length

  std::vector<double> x(n);
  std::vector<double> g(n);
  std::vector<double> v(n);

  // setting x- and g-values
  for (int i=0; i < n; i++){
    x[i] = i*h + h;
    g[i] = g_func(x[i], h);
  }

  double two_thirds = 2./3;
  v[n-1] = two_thirds*(g[n-1] + 0.5*g[n-2]);
  for (int i = n-2; i > 0; i--){
    v[i] = two_thirds*(g[i] + 0.5*g[i-1] + v[i+1]);
  }
  v[0] = 0.5*(g[0] + v[1]);

  // endpoints
  x.insert (x.begin(), 0.);
  x.push_back(1.);
  v.insert (v.begin(), 0.);
  v.push_back(0.);

  // print to problem7_output.txt
  std::string filename = "problem9c_output.txt";
  std::ofstream ofile;
  ofile.open(filename);

  int width = 16;
  int prec = 8;

  for (int i = 0; i < n+2; i++){
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x[i]
          << std::setw(width) << std::setprecision(prec) << std::scientific << v[i]
          << std::endl;
  }

  return 0;
}

// Defenitions
double g_func(double x, double h){
  return h*h*100*exp (-10*x);
}
