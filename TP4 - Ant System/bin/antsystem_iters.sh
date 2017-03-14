#! /bin/bash

file_in=cities.dat
file_out=iter_variation.csv
n_ants=40

while [[ $# -gt 0 ]]; do
  if [[ "$1" == "-in" ]]; then
    shift 
    file_in=$1
  elif [[ "$1" == "-out" ]]; then
    shift 
    file_out=$1
  elif [[ "$1" == "-ants" ]]; then
    shift
    n_ants=$1
  fi 
  
  shift 
done

for i in `seq 1 1 20`;
do
  ./antsystem $file_in -ants $n_ants -iter $i -n 100 -csv $file_out -no_plot 
done 
for i in `seq 40 20 1000`;
do
  ./antsystem $file_in -ants $n_ants -iter $i -n 100 -csv $file_out -no_plot
done

exit 0

