#! /bin/bash
echoerr() { printf "%s\n" "$*" >&2; }

./gp -header
for j in `seq 6 1 20`;
do
    echoerr 'Program length: ' $j
    ./gp -csv -plength $j
done

exit 0
