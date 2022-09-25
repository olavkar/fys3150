//

#include "header.hpp"

int main(){
  int n = 100;
  int N = n-1; //excluding endpoints
  double a = -1.;
  double d = 2.;

  // analytical
  int num = 3; // number of vectors
  arma::mat anal_eig = anal_eigen(N, a, d);
  arma::mat anal_min_eig = arma::mat(N, num).fill(0.);

  for (int i = 1; i <= num; i++){
    anal_min_eig.col(i-1) = anal_eig.col(i);
  }

  // numerical
  arma::mat A = tri_diag(N, a, d);
  arma::mat R = jacobis_rot(A);

  // finding three min. eigenvalues inspired by https://www.tutorialspoint.com/find-the-first-second-and-third-minimum-elements-in-an-array-in-cplusplus-program
  double first = 100000.;
  double secnd = 100000.;
  double third = 100000.;

  int first_id = 0;
  int secnd_id = 0;
  int third_id = 0;

  for (int i = 0; i < N; i++){
    if (std::abs(A(i, i)) < std::abs(first)){
      third = secnd;
      third_id = secnd_id;
      secnd = first;
      secnd_id = first_id;
      first = A(i, i);
      first_id = i;
    }
    else if (std::abs(A(i, i)) < std::abs(secnd)){
      third = secnd;
      third_id = secnd_id;
      secnd = A(i, i);
      secnd_id = i;
    }
    else if (std::abs(A(i, i)) < std::abs(third)){
      third = A(i, i);
      third_id = i;
    }
  }

  std::vector<int> id_list{first_id, secnd_id, third_id};
  arma::mat num_min_eig = arma::mat(N, num).fill(0.);

  for (int i = 0; i < num; i++){
    arma::vec num_min_eig_temp = R.col(id_list[i]);
    if (anal_min_eig(i, 0) > 0 && num_min_eig_temp(i, 0) > 0){ // if-statement to ensure same sign in front of eigenvalue
      num_min_eig.col(i) = num_min_eig_temp;
    }
    else {
      num_min_eig.col(i) = -num_min_eig_temp;
    }
  }

  int width = 20;
  int prec = 8;

  std::string filename = "output.txt";
  std::ofstream ofile;
  ofile.open(filename);

  for (int i = 0; i < num; i++){
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << 0
          << std::setw(width) << std::setprecision(prec) << std::scientific << 0
          << std::endl;

    for (int j = 0; j < N; j++ ){
      ofile << std::setw(width) << std::setprecision(prec) << std::scientific << anal_min_eig(j, i)
            << std::setw(width) << std::setprecision(prec) << std::scientific << num_min_eig(j, i)
            << std::endl;
    }
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << 0
          << std::setw(width) << std::setprecision(prec) << std::scientific << 0
          << std::endl;
  }

  return 0;
}
