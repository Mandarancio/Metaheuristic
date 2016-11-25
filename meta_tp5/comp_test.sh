#!/bin/sh

cd src/
g++ main_matrix.cpp matrix.cpp exmath.cpp -O2 -std=c++11 -o ../bin/test
# clang++ main_matrix.cpp matrix.cpp exmath.cpp -std=c++11 -O3 -o ../bin/test_clang
# g++ main_matrix.cpp matrix.cpp exmath.cpp -Ofast -std=c++11 -o ../bin/test_fast
# g++ main_matrix.cpp matrix.cpp exmath.cpp -O2 -std=c++11 -o ../bin/test_O2
