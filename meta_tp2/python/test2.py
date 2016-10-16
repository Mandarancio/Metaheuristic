#! /usr/bin/python3
import time
import sys


def millis():
    return int(round(time.time() * 1000))


if __name__ == "__main__":
    import QAP
    n = 5
    D = [[0, 1, 1, 2, 3],
            [1, 0, 2, 1, 2],
            [1, 2, 0, 1, 2],
            [2, 1, 1, 0, 1],
            [3, 2, 2, 1, 0]]
    W = [[0, 5, 2, 4, 1],
            [5, 0, 3, 0, 2],
            [2, 3, 0, 0, 0],
            [4, 0, 0, 0, 5],
            [1, 2, 0, 5, 0]]
    
    s0= QAP.Solution([2,3,5,1,4])
    s1 = s0.neighbor(0,2)
    s2 = s1.neighbor(1,3)
    qap = QAP.QAP(n,D,W)
    print(str(s0)+' : '+str(qap.fitness(s0)))
    print(str(s1)+' : '+str(qap.fitness(s1)))
    print("Delta : "+str(qap.delta_fitness(s0,s0[0]-1,s0[2]-1)))
    print(str(s2)+' : '+str(qap.fitness(s2)))
    print("Delta : "+str(qap.delta_fitness(s0,s0[1]-1,s0[3]-1)) )
    # import numpy as np
    # f = open('1.dat')
    # print(f.read())
    #
    # print(matrix)
    #
