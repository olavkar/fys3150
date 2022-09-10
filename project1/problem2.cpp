// Problem 2
// Makes two arrays; one of x-values between 0 and 1, and one for the
// corresponding u(x)-values, where:
// u(x) = 1 - (1 - e**(-10))*x - e**(-10*x)

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

// Declerations
double u_func(double x);

// Main
int main(){
  // Creating and filling x- and u-vectors
  std::vector<double> x; // empty list of x-values
  std::vector<double> u; // empty list of u(x)-values

  int n = 1000; // number of points
  double s = 1.0/(n-1); // step lenght (n-1 steps)
  for (int i = 0.0; i < n; i++){
    x.push_back(i*s);
    u.push_back(u_func(i*s));
  }

  // Creating and writing to text file
  std::string filename = "problem2_output.txt";
  std::ofstream ofile;
  ofile.open(filename);

  int width = 12;
  int prec = 4;

  for (int i = 0; i < n; i++){
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x[i]
          << std::setw(width) << std::setprecision(prec) << std::scientific << u[i]
          << std::endl;
  }

  return 0;
}

// Defenitions
double u_func(double x){
  return (1 - (1 - exp (-10))*x - exp (-10*x));
}
