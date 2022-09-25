// tests max_offdiag_symmetric() on a matrix

#include "header.hpp"

int main(){
  int N = 4;
  int k = 0;
  int l = 0;
  arma::mat matrix = arma::mat(N, N).fill(0.);

  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;
  matrix(0, 3) = 0.5;
  matrix(3, 0) = 0.5;
  matrix(1, 2) = -0.7;
  matrix(2, 1) = -0.7; // more efficient way to assign irregular elements?

  double max = max_offdiag_symmetric(matrix, k, l);

  std::cout << max << " " << k << " " << l << std::endl;

  return 0;
}
