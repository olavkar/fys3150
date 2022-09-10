#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

int main(){
  std::string filename = "output.txt";

  std::ofstream ofile;
  ofile.open(filename);

  double x_min = 0.0;
  double x_max = 1.0;
  int steps = 10;
  double h = (x_max-x_min)/steps;

  int width = 12;
  int prec = 4;

  double x = x_min;
  double y = x*x;

  for (int i = 0; i <= steps; i++){
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x
          << std::setw(width) << std::setprecision(prec) << std::scientific << y
          << std::endl;

    x += h;
    y = x*x;
  }

  ofile.close();

  return 0;
}
