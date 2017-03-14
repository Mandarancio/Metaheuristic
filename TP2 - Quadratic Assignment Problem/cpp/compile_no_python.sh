#! /bin/sh
g++ main.cpp qap.cpp histo.cpp -D PLOT=0 -o bin/analyser
g++ brute_force.cpp qap.cpp histo.cpp  -D PLOT=0 -o bin/brute_force
g++ generateNDW.cpp -o bin/generator
g++ landscape.cpp histo.cpp qap.cpp -D PLOT=0 -o bin/landscape
g++ statistic.cpp qap.cpp histo.cpp -D PLOT=0 -D HIPERF=1 -o bin/statistic 

