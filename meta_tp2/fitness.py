#! /usr/bin/python3
import sys
import QAP
import tp_import as tpi
argv = sys.argv[1:]
if len(argv) != 2:
    sys.exit(0)
path = ''
sol = []
for a in argv:
    if a.startswith('--file='):
        path = a.split('=')[1]
    if a.startswith('--solution='):
        seq = a.split('=')[1].split(',')
        for s in seq:
            sol.append(int(s))
n, D, W = tpi.import_dat(path)
I = QAP.QAP(n, D, W)
sol = QAP.Solution(sol)
print(sol)
print(I.fitness(sol))
