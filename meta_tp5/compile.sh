#!/bin/sh

cd src/
g++ main.cpp pso.cpp display.cpp exmath.cpp meta.cpp -O3 -std=c++11 -o ../bin/steps -lpython2.7 
