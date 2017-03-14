#!/bin/sh
cd ..
echo 'compile analyse...'
g++ main.cpp exmath.cpp annealing.cpp tsp.cpp greedy.cpp meta.cpp -o bin/analyse -D NO_PLOT=1 -O2 -g
echo 'compile generator...'
g++ generator.cpp -o bin/generator
echo 'compile landscape...'
g++ landscape.cpp tsp.cpp exmath.cpp meta.cpp  -O2 -D NO_PLOT=1 -o bin/landscape
echo 'compile parallel_tempering...'
g++ parallel_tempering.cpp exmath.cpp annealing.cpp tsp.cpp greedy.cpp meta.cpp -o bin/parallel_tempering -D NO_PLOT=1 -O2 
echo 'done!'
