#!/bin/bash

cd src/
g++ main.cpp antsystem.cpp display.cpp exmath.cpp greedy.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/antsystem -lpython2.7 
g++ main_greedy.cpp display.cpp exmath.cpp greedy.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/greedy -lpython2.7 
g++ main_annealing.cpp display.cpp exmath.cpp annealing.cpp tsp.cpp meta.cpp -O3 -std=c++11 -o ../bin/annealing -lpython2.7 
