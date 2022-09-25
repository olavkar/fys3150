// Solves the eigenvalue-eigenvector problem using Jacobi's Rotaion method,
// and prints the solution to the terminal.

#include "header.hpp"

int main(){
  int N = 6;
  double a = -1.;
  double d = 2.;

  arma::mat A = tri_diag(N, a, d);
  arma::mat R = jacobis_rot(A);

  std::cout << "Eigenvalues:\n";
  for (int i=0; i<N; i++){
      std::cout << A(i, i) << std::endl;
  }

  std::cout << "Eigenvectors (vertical): \n";
  int width = 12;
  int prec = 4;

  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
      std::cout << std::setw(width) << std::setprecision(prec) << std::scientific << R(i, j);
    }
    std::cout << std::endl;
  }

  return 0;
}
