#! /bin/bash
echoerr() { printf "%s\n" "$*" >&2; }

./gp -header
for pc in `LANG=en_US seq 0.00 0.1 1.0`;
do
  echoerr 'Pc: ' $pc
  ./gp -csv -plength 13 -pop 30 -pm 0.08 -pc $pc
done

exit 0
