// Problem 10 using special algorithm
// Uses algorithm found in problem 9a

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>

// Declerations
double g_func(double x, double h);

// Main
int main(){
  // Loop over all n_steps values
  std::vector<int> n_steps = {10, 100, 1000, 10000, 100000, 1000000};

  for (int k=0; k<n_steps.size();k++){
    //loop over same n_steps value to increase accuracy of measurment
    int m = 100; // number of loops. More than 100 probably not worth the time
    double total_time=0; // total time for all loops

    for (int j=0; j<m; j++){
      // defining vectors
      int n = n_steps[k]; // number of non-end points
      double h = 1./(n+1); // step length

      std::vector<double> x(n);
      std::vector<double> g(n);
      std::vector<double> v(n);

      // setting x- and g-values
      for (int i=0; i < n; i++){
        x[i] = i*h + h;
        g[i] = g_func(x[i], h);
      }

      auto t1 = std::chrono::high_resolution_clock::now(); // start of algorithm

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

      auto t2 = std::chrono::high_resolution_clock::now(); // end of algorithm (could skip endpoints but whatever)
      double duration_seconds = std::chrono::duration<double>(t2 - t1).count();
      total_time += duration_seconds;
    }

    double average_time = total_time/m;
    std::cout << average_time << std::endl; // cant be bothered with outputfiles anymore
    // yes, even comments are copy-pasted
  }
  return 0;
}

// Defenitions
double g_func(double x, double h){
  return h*h*100*exp (-10*x);
}
