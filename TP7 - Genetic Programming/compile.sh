#!/bin/sh

cd src/
g++ main.cpp gp.cpp -O3 -std=c++11 -o ../bin/gp
g++ main_plot.cpp exmath.cpp -O3 -std=c++11 -o ../bin/gp_plot -lpython2.7
g++ landscape.cpp exmath.cpp -O3 -std=c++11  -o ../bin/landscape -lpython2.7
