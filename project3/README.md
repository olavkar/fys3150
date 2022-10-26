Penning trap model
------------------
To run a main.exe file using the Particle class and PenningTrap:

g++ main.cpp src/Particle.cpp src/PenningTrap.cpp -I include/ -o main.exe

Look through Particle.hpp and PenningTrap.hpp for the accompanying functions and
variables in each class.

The main.cpp and plot.py files should not be treated as programs that will give
you all the plots in the report, but as templates for how to use and extract data
from the classes. main.cpp currently gives correct positional data to be used for
calculating relative error for n=8000.

The .txt files were obtained by the command

./main >> some_file_name.txt
