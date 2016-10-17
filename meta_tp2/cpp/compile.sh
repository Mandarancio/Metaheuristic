#! /bin/sh
g++ main.cpp qap.cpp histo.cpp -lpython2.7 -D PLOT=1 -o bin/analyser
g++ brute_force.cpp qap.cpp histo.cpp -lpython2.7 -D PLOT=1 -o bin/brute_force
g++ generateNDW.cpp -o bin/generator
g++ landscape.cpp histo.cpp qap.cpp -lpython2.7 -D PLOT=1 -o bin/landscape
g++ statistic.cpp qap.cpp histo.cpp -D PLOT=1 -D HIPERF=1 -lpython2.7 -o bin/statistic 

