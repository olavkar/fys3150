### Project 2

### Problem 2
1. Compiling and linking
To compile and link run the commands

c++ problem2.cpp -llapack -o problem2

Linking to lapack here was the only way to get arma::eig_sym to work. You might
not need to link lapack, but you might get this error (copy-pasted from terminal):

/usr/bin/ld: /tmp/cchIMssO.o: in function `void arma::lapack::syevd<double>(char*, char*, int*, double*, int*, double*, double*, int*, int*, int*, int*)':
problem2.cpp:(.text._ZN4arma6lapack5syevdIdEEvPcS2_PiPT_S3_S5_S5_S3_S3_S3_S3_[_ZN4arma6lapack5syevdIdEEvPcS2_PiPT_S3_S5_S5_S3_S3_S3_S3_]+0x5d): undefined reference to `dsyevd_'
/usr/bin/ld: /tmp/cchIMssO.o: in function `void arma::lapack::syev<double>(char*, char*, int*, double*, int*, double*, double*, int*, int*)':
problem2.cpp:(.text._ZN4arma6lapack4syevIdEEvPcS2_PiPT_S3_S5_S5_S3_S3_[_ZN4arma6lapack4syevIdEEvPcS2_PiPT_S3_S5_S5_S3_S3_]+0x57): undefined reference to `dsyev_'

2. Running
To run just type the command

./problem2

The elements of arma_eigen and anal_eigen will be listed side by side with the
corresponding value in the other matrix.

### Problem 3
1. Compiling and linking
To compile and link run the commands

c++ problem3.cpp -llapack -o problem3

2. Running
Run the commands

./problem3

The max value and its indices will show in the terminal.

### Problem 4
1. Config
Make sure line 7 in problem4.cpp reads:

int N = 6;

2. Compiling and linking
Run the commands

c++ problem4.cpp -llapack -o problem4

3. Running
Run the commands

./problem4

To compare the results with problem 2, also run

./problem2

Sadly for the user, the eigenvalues and eigenvectors are not sorted for ease of comparison.

### Problem 5 a)
1. Config
Make sure line 8 in problem5.cpp reads

bool random_dense_mat = false;

2. Compiling and linking
Run the commands

c++ problem5.cpp -llapack -o problem5

3. Running
To run type the commands

./problem5

### Problem 5 b)
1. Config
Make sure line 8 in problem5.cpp reads

bool random_dense_mat = true;

2. Compiling and linking
Run the commands

c++ problem5.cpp -llapack -o problem5

3. Running
To run type the commands

./problem5

### Problem 6 a)
1. Config
Make sure n = 10 in both problem6.cpp and problem6.py

2. Compiling and linking
To compile and link run the commands

c++ problem6.cpp -llapack -o problem6

3. Running
Run the commands

./problem6

python problem6.py

This creates a .txt file called output_10.txt and a .pdf called output_10.pdf.

### Problem 6 b)
1. Config
Make sure n = 100, otherwise everything is the same as in a). 
