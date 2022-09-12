I didn't format this README to look good on Github, sorry :(
  
### Project 1 ###
This should explain how to run the code used in project 1 to get the same
results.

###############
## Problem 2 ##
# Config
In problem2.cpp let/write line 22 to be:

int n = 1000;

# Compile
Run the commands

c++ problem2.cpp -o problem2

# Run
Run the commands

./problem2

python plot_problem2.py

This will leave you with 3 new files:
-problem2
-problem2_output.txt
-problem2_output.pdf

################
## Problem 7a ##
# Config
In problem7.cpp let/write line 17 to be:

int n = 1000;

# Compile
Run the commands

c++ problem7.cpp -o problem7

# Run
Run the commands

./problem7

python plot_problem7.py

This will leave you with 3 new files:
-problem7
-problem7_output.txt
-problem7_output.pdf

################
## Problem 7b ##
# Config
In problem7b.cpp, for each of the n_steps-values write in line 22:

int n = n_steps + 1;

where n_steps is the integer, example:

int n = 100 + 1;

# Compile
Run the commands

c++ problem7b.cpp -o problem7b

# Run
Run the commands

./problem7b

python plot_problem7b.py

This will leave you with 4 new files:
-problem7b
-problem7b2_output.txt
-problem7b7_output.txt
-problem7b_output.pdf

####################
## Problem 8a & b ##
# Config
In problem8.cpp let/set line 19 to be:

std::vector<int> n_steps = {10, 100, 1000};

And lines 77-78:

int width = 16;
int prec = 8;

# Compile
Run the commands

c++ problem8.cpp -o problem8

# Run
Run the commands

./problem8

python problem8.py

This leaves 5 new files:
-problem8
-problem8_10_output.txt
-problem8_100_output.txt
-problem8_1000_output.txt
-problem8_output.pdf

################
## Problem 8c ##
# Config
In problem8.cpp let/set line 19 to be:

std::vector<int> n_steps = {10, 100, 1000, 10000, 100000, 1000000, 10000000};

And lines 77-78:

int width = 20;
int prec = 12;

# Compile
Run the commands

c++ problem8.cpp -o problem8

# Run
Run the commands

./problem8 <-- Kinda slow due to 1e7 n_steps

python problem8c.py

This leaves 9 new files:
-problem8
-problem8_10_output.txt
-problem8_100_output.txt
-problem8_1000_output.txt
-problem8_10000_output.txt
-problem8_100000_output.txt
-problem8_1000000_output.txt
-problem8_10000000_output.txt
-problem8_output.pdf

Read the terminal for full table values.
Remember to delete these .txt files after use; the last one is ~610MB.

################
## Problem 9c ##
# Compile
Run the commands

c++ problem9c.cpp -o problem9c

# Run
Run the commands

./problem9c

This gives 2 new files:
-problem9c
-problem9c_output.txt

################
## Problem 10 ##
# Compile
Run the commands

c++ problem10_gen.cpp -o problem10_gen

c++ problem10_spc.cpp -o problem10_spc

# Run
Run the commands

./problem10_gen

./problem10_spc

Read the results from the terminal (I approximated to 3 significant figures)
