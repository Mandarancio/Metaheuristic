#! /usr/bin/python3
import time
import sys


def millis():
    return int(round(time.time() * 1000))


def display_help():
    print('TP2 Help (Martino Ferrari)\n \
    \r--file=FILENAME to load a matrix file (ex: 1.dat)\n \
    \r--iterations=INT t_max to pass to the tabu meta-heuristic\n \
    \r--lcoef=FLOAT variation of the l parameter\n \
    \r--diversification=BOOL diversification yes or no\n\
    \r--help show this help')
    sys.exit()


if __name__ == "__main__":
    import numpy as np
    import QAP
    import tp_import as tp_imp
    import gc
    argv = sys.argv
    path = '1.dat'
    iterations = 1000
    l_coef = 1.0
    diversification = True
    Is = []
    n_times = 10
    if len(argv) < 2:
        display_help()
    for a in argv:
        if a.startswith('--file='):
            path = a.split('=')[1]
        elif a.startswith('--iterations='):
            iterations = int(a.split('=')[1])
        elif a.startswith('--lcoef='):
            l_coef = float(a.split('=')[1])
        elif a == '--help':
            display_help()
        elif a.startswith('--diversification='):
            diversification = a.split('=')[1] == 'true'

    T = int(50/n_times)
    TS = ''
    for i in range(0, T):
        TS += '+'
    TT = ''
    for i in range(0, 50):
        TT += ' '

    n, D, W = tp_imp.import_dat(path)

    print('Matrices File: '+str(path))
    print('Iterations: '+str(iterations))
    print('L Coeff: '+str(l_coef))
    print('N: '+str(n))
    l = round(n*l_coef)
    print('L: '+str(l))
    print('N exec: '+str(n_times))
    print('Diversification: '+str(diversification))
    I = QAP.QAP(n, W, D, tabu_length=l)
    t0 = millis()
    bf = []
    for i in range(0, n_times):
        I.reset()
        gc.collect()
        s = QAP.rand_solution(n)
        sys.stdout.write('\r'+str(round(100*i/n_times))+'% |'+TT+'|')
        s, f = I.U(s, iterations)
        bf.append(f)
        TT = TT[:T*i]+TS+TT[T*i+T:]
        Is.extend(I.Is())

    t1 = millis()

    sys.stdout.write('\r100% |'+TT+'|\n')

    bf = np.array(bf)
    min_f = np.min(bf)
    max_f = np.max(bf)
    avg_f = np.mean(bf)
    dist_f = (avg_f-min_f) if (avg_f-min_f > max_f-avg_f) else (max_f-avg_f)
    print('Total time: '+str((t1-t0)/1000)+' s')
    print('Time per iteration: '+str((t1-t0)/(iterations*n_times))+' ms')
    print('Best Fitness: '+str(min_f))
    print('Avarage: '+str(avg_f))
    print('Distance: '+str(dist_f))
    print('Results: '+str(bf))
