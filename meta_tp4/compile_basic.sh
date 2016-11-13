#!/bin/sh

cd src/
g++ main.cpp antsystem.cpp display.cpp exmath.cpp greedy.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/antsystem -D NO_PLOT=1
g++ main_greedy.cpp display.cpp exmath.cpp greedy.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/greedy -D NO_PLOT=1
g++ main_annealing.cpp display.cpp exmath.cpp annealing.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/annealing -D NO_PLOT=1
