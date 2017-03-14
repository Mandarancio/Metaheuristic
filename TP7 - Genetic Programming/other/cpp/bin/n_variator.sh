#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for j in `seq 10 10 100`;
do
    ./ga -bit 16 -evals 10 -pm 0.1 -pc 0.6 -pop $j -it 50
done

exit 0
