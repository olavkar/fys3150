// Prints the elements of the eigenvalues and eigenvectors for visual comparison
// (look at the console and see that they are the same)

#include "header.hpp"

int main(){
  int N = 6;
  double a = -1.;
  double d = 2.;

  arma::mat k = tri_diag(N, a, d);
  arma::mat arma_eig = arma_eigen(k);
  arma::mat anal_eig = anal_eigen(N, a, d);

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      std::cout << arma_eig(j, i) << " " << anal_eig(j, i) << std::endl;
    }
    std::cout << "\n" << std::endl;
  }
  return 0;
}
