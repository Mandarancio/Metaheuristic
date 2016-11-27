#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for i in `seq 1 1 50`;
do
  ./pso -csv -tmax 70 -npart 40 -omega 0.75 -c1 1.8 -c2 1.2 -vmax 0.35 #2>/dev/null
  sleep 0.001
done

exit 0
