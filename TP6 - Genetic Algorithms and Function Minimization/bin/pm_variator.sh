#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for j in `LC_NUMERIC="en_US.UTF-8" seq 0.01 0.01 0.1`;
do

    ./ga -bit 16 -evals 10 -pm $j -pc 0.6 -pop 100 -it 50
done

exit 0
