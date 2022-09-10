// Problem 7
// Solves Av_=g_ (_ = vector) using algorithm from Problem 6

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
  double h = 1./(n+2); // step length
  std::vector<double> a(n, -1.); // subdiagonal
  std::vector<double> b(n, 2.); // main diagonal
  std::vector<double> c(n, -1.); // superdiagonal

  std::vector<double> x(n);
  std::vector<double> g(n);
  std::vector<double> v(n);

  // setting x- and g-values
  for (int i=0; i < n; i++){
    x[i] = i*h + h;
    g[i] = g_func(x[i], h);
  }

  // forward sub
  for (int i=1; i < n; i++){
    g[i] = g[i] - a[i]/b[i-1]*g[i-1];
    b[i] = b[i] - a[i]/b[i-1]*c[i-1];
  }

  // back sub
  v[n-1] = g[n-1]/b[n-1];
  for (int i=n-2; i>=0; i--){
    v[i] = (g[i] - c[i]*v[i+1])/b[i];
  }

  // endpoints
  x.insert (x.begin(), 0.);
  x.push_back(1.);
  v.insert (v.begin(), 0.);
  v.push_back(0.);

  // print to problem7_output.txt
  std::string filename = "problem7_output.txt";
  std::ofstream ofile;
  ofile.open(filename);

  int width = 12;
  int prec = 4;

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
