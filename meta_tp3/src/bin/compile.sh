#!/bin/sh
cd ..
g++ main.cpp exmath.cpp annealing.cpp tsp.cpp greedy.cpp -o bin/analyse -lpython2.7 -O2 
g++ stepper.cpp annealing.cpp tsp.cpp -o bin/stepper -lpython2.7 -g