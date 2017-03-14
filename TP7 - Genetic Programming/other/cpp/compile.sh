#!/bin/sh

cd src/
g++ main.cpp geneticalg.cpp exmath.cpp matrix.cpp -O3 -o ../bin/ga
echo "ga: DONE"
