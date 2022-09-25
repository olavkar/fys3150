// Print the number of rotations needed in Jacobi's Rotation method to the
// tolerance (10^-8).

#include "header.hpp"

int main(){
  bool count_rotations = true;
  bool random_dense_mat = false;
  double a = -1.;
  double d = 2.;

  std::vector<int> N;
  N.push_back(10);
  N.push_back(20);
  N.push_back(40);
  N.push_back(80);
  N.push_back(160);

  for (int i = 0; i < N.size(); i++){

    arma::mat A = tri_diag(N[i], a, d);
    arma::mat R = jacobis_rot(A, count_rotations, random_dense_mat);
  }
  return 0;
}
