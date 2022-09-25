// Main cpp file for project 2

# include "header.hpp"

int main(){
  int problem = 2;

  int N = 6;
  double a = -1.;
  double d = 2.;

  if (problem == 2){
    arma::mat k = tri_diag(N, a, d);
    arma::mat arma_eig = arma_eigen(k);
    arma::mat anal_eig = anal_eigen(N, a, d);

    for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
        std::cout << arma_eig(j, i) << " " << anal_eig(j, i) << std::endl;
      }
      std::cout << "\n" << std::endl;
    }
  }

  if (problem == 3){
    1;
  }

  if (problem == 4){
    1;
  }

  if (problem == 5){
    1;
  }

  return 0;
}
