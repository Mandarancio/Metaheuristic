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
    \r--help show this help')
    sys.exit()

if __name__ == "__main__":
    import numpy as np
    from scipy.stats import norm, skewnorm
    import QAP
    import tp_import as tp_imp
    import matplotlib.pyplot as plt
    argv = sys.argv
    path = '1.dat'
    iterations = 1000
    l_coef = 1.0
    diversification = True
    Is = []
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
    n, D, W = tp_imp.import_dat(path)

    print('Matrices File: '+str(path))
    print('Iterations: '+str(iterations))
    print('L Coeff: '+str(l_coef))
    print('N: '+str(n))
    l = round(l_coef*n)
    print('L: '+str(l))
    print('Diversification: '+str(diversification))
    I = QAP.QAP(n, D, W, tabu_length=l)
    t0 = millis()
    s = QAP.rand_solution(n)
    print('Start solution: '+str(s))
    s, f = I.U(s, iterations, diversification)
    Is.append(f)
    Is = I.Is()

    t1 = millis()

    print('Best Solution: '+str(s)+' : '+str(f))
    print('Computed f: '+str(I.fitness(s)))
    print('Total time: '+str((t1-t0)/1000)+' s')
    print('Time per iteration: '+str((t1-t0)/(iterations))+' ms')
    x = np.linspace(550, 800, 250)
    mu, sigma = norm.fit(Is)
    print('Mu: '+str(mu))
    print('Sigma: '+str(sigma))
    y = norm.pdf(x, mu, sigma)
    a, loc, scale = skewnorm.fit(Is)
    yyy = skewnorm.pdf(x, a, loc, scale)
    # print(yyy)
    # print(y)
    plt.hist(Is, bins=50, alpha=0.5, range=[550, 800], normed=True)
    plt.plot(x, y)
    plt.plot(x, skewnorm.pdf(x, a, loc, scale))
    plt.xlabel('Fitness')
    plt.title('Normalized Fitness histogram')
    plt.xlim(550, 800)
    plt.figure()
    plt.plot(Is)
    plt.show()
    # print()
    # tm = QAP.TabuMatrix(5,5)
    # tm.tabu(s,0,2)
    # print(tm)

    #
    # D = [[0, 1, 1, 2, 3],
    #      [1, 0, 2, 1, 2],
    #      [1, 2, 0, 1, 2],
    #      [2, 1, 1, 0, 1],
    #      [3, 2, 2, 1, 0]]
    # W = [[0, 5, 2, 4, 1],
    #      [5, 0, 3, 0, 2],
    #      [2, 3, 0, 0, 0],
    #      [4, 0, 0, 0, 5],
    #      [1, 2, 0, 5, 0]]
    # import numpy as np
    # f = open('1.dat')
    # print(f.read())
    #
    # print(matrix)
    #
