import NKLandscape as NKL
import numpy as np
import random

def generateSimpleS(N):
    res = []
    for i in range(0, N*1000 ):
        res.append(NKL.get_rand_bit_array(N).value())
    return res


def generateS(N):
    size = 2 ** N
    return np.linspace(0, size - 1, num=size, dtype=int)


def landscape(s, f: NKL.NKFitness):
    fx = []
    for x in s:
        fx.append(f.fitness(NKL.BitArray.from_number(x)))
    return np.array(fx)


N = 21
locals_fitness = [NKL.NKFitness(0, {0b0: 0, 0b1: 1}),
                  NKL.NKFitness(1, {0b00: 2, 0b01: 3, 0b10: 2, 0b11: 0}),
                  NKL.NKFitness(2, {0b000: 0, 0b001: 1, 0b010: 1, 0b011: 0, 0b100: 2, 0b101: 0, 0b110: 0, 0b111: 0})]
x = sorted(generateSimpleS(N))
# x=np.array([0,1,2,4,3,6,5,7])
y1 = landscape(x, locals_fitness[0])
y2 = landscape(x, locals_fitness[1])
y3 = landscape(x, locals_fitness[2])

import matplotlib.pyplot as plt

plt.plot(x, y1, label='K0')
plt.plot(x, y2, label='K1')
plt.plot(x, y3, label='K2')
plt.xlim(0, 2 ** N - 1)
plt.legend()
plt.show()
