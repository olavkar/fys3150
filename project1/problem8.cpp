// Problem 8
// problem2.cpp and problem7.cpp smashed toghether and modified to output
// on the same file, and additional outputfiles as per the number of n_steps-
// values.

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

// Declerations
double u_func(double x);
double g_func(double x, double h);

// Main
int main(){
    std::vector<int> n_steps = {10, 100, 1000, 10000, 100000, 1000000, 10000000};

    for (int i=0; i < n_steps.size(); i++){
      std::stringstream temp;
      temp << "problem8_" << n_steps[i] << "_output.txt";
      std::string filename = temp.str();

      // Problem 2 section
      // Creating and filling x- and u-vectors
      std::vector<double> x; // empty list of x-values
      std::vector<double> u; // empty list of u(x)-values

      int n = n_steps[i]+3; // number of points
      double s = 1.0/(n-1); // step lenght (n-1 steps)
      for (int i = 0; i < n; i++){
        x.push_back(i*s);
        u.push_back(u_func(i*s));
      }

      // Problem 7a section
      n = n - 2; // to have total number of points equal to above
      double h = 1./(n+1); // step length
      std::vector<double> a(n, -1.); // subdiagonal
      std::vector<double> b(n, 2.); // main diagonal
      std::vector<double> c(n, -1.); // superdiagonal

      std::vector<double> x1(n); // different from x above
      std::vector<double> g(n);
      std::vector<double> v(n);

      // setting x- and g-values
      for (int i=0; i < n; i++){
        x1[i] = i*h + h;
        g[i] = g_func(x1[i], h);
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
      x1.insert (x1.begin(), 0.);
      x1.push_back(1.);
      v.insert (v.begin(), 0.);
      v.push_back(0.);

      // Creating and writing to text file
      std::ofstream ofile;
      ofile.open(filename);

      int width = 24;
      int prec = 16;

      for (int i = 1; i < n+1; i++){
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x1[i]
              << std::setw(width) << std::setprecision(prec) << std::scientific << u[i]
              << std::setw(width) << std::setprecision(prec) << std::scientific << v[i]
              << std::endl;
      }
      ofile.close();

    }
  return 0;
}

// Defenitions
double u_func(double x){
  return (1 - (1 - exp (-10))*x - exp (-10*x));
}
double g_func(double x, double h){
  return h*h*100*exp (-10*x);
}
