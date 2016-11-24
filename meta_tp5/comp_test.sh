#!/bin/sh

cd src/
g++ main_matrix.cpp matrix.cpp exmath.cpp -O3 -std=c++11 -o ../bin/test -g
