// Problem 10 using general alg.
// Solves Av_=g_ (_ = vector) using algorithm from Problem 6

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

      auto t1 = std::chrono::high_resolution_clock::now(); // start of algorithm

      // forward sub
      for (int i=1; i < n; i++){
        double temp = a[i]/b[i-1]; // THE only optimization I could be bothered with in general algorithm
        g[i] = g[i] - temp*g[i-1];
        b[i] = b[i] - temp*c[i-1];
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

      auto t2 = std::chrono::high_resolution_clock::now(); // end of algorithm (could skip endpoints but whatever)
      double duration_seconds = std::chrono::duration<double>(t2 - t1).count();
      total_time += duration_seconds;
    }
    double average_time = total_time/m;
    std::cout << average_time << std::endl; // cant be bothered with outputfiles anymore
  }
  return 0;
}

// Defenitions
double g_func(double x, double h){
  return h*h*100*exp (-10*x);
}
