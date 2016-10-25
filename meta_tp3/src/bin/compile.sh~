#!/bin/sh
cd ..
echo 'compile analyse...'
g++ main.cpp exmath.cpp annealing.cpp tsp.cpp greedy.cpp meta.cpp -o bin/analyse -lpython2.7 -O2 
echo 'compile stepper...'
g++ stepper.cpp annealing.cpp tsp.cpp meta.cpp -o bin/stepper -lpython2.7 
echo 'compile generator...'
g++ generator.cpp -o bin/generator
echo 'compile landscape...'
g++ landscape.cpp tsp.cpp exmath.cpp meta.cpp -lpython2.7 -O2 -o bin/landscape
echo 'compile parallel_tempering...'
g++ parallel_tempering.cpp exmath.cpp annealing.cpp tsp.cpp greedy.cpp meta.cpp -o bin/parallel_tempering -lpython2.7 -O2 
echo 'done!'
