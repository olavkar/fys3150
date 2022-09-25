#include <armadillo>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

// Declerations (necessary?)
arma::mat tri_diag(int N, double a, double d);

arma::mat arma_eigen(arma::mat A);

arma::mat anal_eigen(int N, double a, double d);

double max_offdiag_symmetric(const arma::mat& A, int& k, int& l);

arma::mat jacobis_rot(arma::mat& A, bool count_rotations, bool random_dense_mat, double tolerance);

// Definitions
arma::mat tri_diag(int N, double a, double d){
  // Returns tridiagonal matrix with sub- and superdiagonal elements a and
  // main diagonal elements d.
  int n = N + 1;
  double h2 = (1./n)*(1./n);
  a = a/h2;
  d = d/h2;

  arma::mat temp = arma::mat(N, N).fill(0.);
  temp(0) = d;
  temp(0, 1) = a;
  temp(N-1, N-1) = d;
  temp(N-1, N-2) = a;

  for (int i = 1; i < N-1; i++){
    temp(i, i) = d;
    temp(i, i+1) = a;
    temp(i, i-1) = a;
  }

  return temp;
}

arma::mat arma_eigen(arma::mat A){
  // Solves the eigenvalue-vector problem using armadillos in-built solver .
  // Returns an N x (N+1) matrix where the first column is the eigenvalues of A
  // and the rest are the eigenvectors of A.
  arma::vec eigval;
  arma::mat eigvec;

  arma::eig_sym(eigval, eigvec, A);

  int N = eigval.size();
  arma::mat eigen(N,N+1);
  eigen.col(0) = eigval;
  for (int i = 1; i <= N; i++){
    eigen.col(i) = arma::normalise(eigvec.col(i-1));
  }

  return eigen;
}

arma::mat anal_eigen(int N, double a, double d){
  // Solves the eigenvalue-vector problem using the analytical solutions.
  // Returns an N x (N+1) matrix where the first column is the eigenvalues of A
  // and the rest are the eigenvectors of A.
  int n = N + 1;
  double h2 = (1./n)*(1./n);
  a = a/h2;
  d = d/h2;

  arma::vec eigval = arma::vec(N).fill(0.);
  arma::mat eigvec = arma::mat(N, N).fill(0.);

  for (int i = 1; i <= N; i++){
    eigval(i-1) = d + 2*a*cos(i*M_PI/n);
    for (int j = 1; j <= N; j++){
      eigvec(i-1, j-1) = sin(j*i*M_PI/n);
    }
  }

  arma::mat eigen(N,N+1);
  eigen.col(0) = eigval;
  for (int i = 1; i <= N; i++){
    eigen.col(i) = arma::normalise(eigvec.col(i-1));
  }

  return eigen;
}

double max_offdiag_symmetric(const arma::mat& A, int& k, int& l){
  int N = sqrt(A.size());
  double max_cand = 0; // candidate for max value

  for (int i = 1; i < N; i++){
    for (int j = 0; j < i; j++){
      if (std::abs(A(i, j)) > std::abs(max_cand)){
        max_cand = A(i, j);
        k = i;
        l = j;
      }
    }
  }
  return max_cand;
}

arma::mat jacobis_rot(arma::mat& A, bool count_rotations = false, bool random_dense_mat = false, double tolerance = pow(10, -8)){
  // Solves the eigenvalue-eigenvector problem using Jacobi's Rotation method.
  // Returns the rotation matrix and overwrites the input matrix A with the diagonalised one.
  int N = sqrt(A.size());
  int k = 0;
  int l = 0;

  if (random_dense_mat){
    A = arma::mat(N, N).randn();
    A = arma::symmatu(A);
  }

  // 1
  arma::mat R = arma::mat(N, N).fill(0.);
  for (int i = 0; i < N; i++){
    R(i, i) = 1.;
  }

  // 2
  double max = max_offdiag_symmetric(A, k, l);

  // 3
  int n_loops = 0;
  while (std::abs(max) > tolerance){
    // 3.1
    double tau = (A(l, l) - A(k, k))/(2.*A(k, l));
    double t = 0;

    // 3.2
    if (tau > 0){
      t = 1./(tau + std::sqrt(1. + tau*tau));
    }
    else {
      t = -1./(-tau + std::sqrt(1. + tau*tau));
    }

    double c = 1./std::sqrt(1. + t*t);
    double s = c*t;

    // 3.3
    double akk = A(k, k);
    A(k, k) = A(k, k)*c*c - 2.*A(k, l)*c*s + A(l, l)*s*s;
    A(l, l) = A(l, l)*c*c + 2.*A(k, l)*c*s + akk*s*s; // <-- this was a pain to notice
    A(k, l) = 0.;
    A(l, k) = 0.;

    for (int i=0; i < N; i++){
      if (i != k && i != l){
        double aik = A(i, k);
        A(i, k) = A(i, k)*c - A(i, l)*s;
        A(k, i) = A(i, k);

        A(i, l) = A(i, l)*c + aik*s;
        A(l, i) = A(i, l);
      }

    // 3.4
      double rik = R(i, k);
      R(i, k) = R(i, k)*c - R(i, l)*s;
      R(i, l) = R(i, l)*c + rik*s;

    }

    // 3.5
    max = max_offdiag_symmetric(A, k, l);

    n_loops += 1;
  }

  R = arma::normalise(R);

  // problem 5 related
  if (count_rotations){
    std::cout << "N=" << N << ", rotations=" << n_loops << std::endl;
  }
  return R;
}
