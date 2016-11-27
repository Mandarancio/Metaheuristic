#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for i in `seq 1 1 50`;
do
  ./pso -csv -tmax 70 -npart 30 -omega 0.75 -c1 0.3 -c2 0.2 -vmax 0.3 #2>/dev/null
done

exit 0
