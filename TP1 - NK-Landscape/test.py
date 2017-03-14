from NKLandscape import BitArray, NKFitness, get_rand_bit_array, det_high_climbing, prob_high_climbing
import numpy as np
import matplotlib.mlab as mlab

import random


def analyse_solutions(solutions, label=''):
    '''
    Plot solutions diversity
    :param solutions:
    :param label:
    :return:
    '''
    diff = []
    N = len(solutions)
    for i in range(0, N - 1):
        for j in range(i + 1, N):
            diff.append(solutions[i] - solutions[j])
    plt.hist(diff, bins=20, color='g', alpha=0.6, normed=True)  # ,bins=20)
    plt.title(label)
    plt.grid(True)
    mean = np.mean(diff)
    variance = np.var(diff)
    sigma = np.sqrt(variance)
    x = np.linspace(0, 22, 100)
    plt.plot(x, mlab.normpdf(x, mean, sigma))

    # plt.show()
    return


random.seed()

locals_fitness = [NKFitness(0, {0b0: 2, 0b1: 1}),
                  NKFitness(1, {0b00: 2, 0b01: 3, 0b10: 2, 0b11: 0}),
                  NKFitness(2, {0b000: 0, 0b001: 1, 0b010: 1, 0b011: 0, 0b100: 2, 0b101: 0, 0b110: 0, 0b111: 0})]
#
# bits = BitArray([1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1])
# print(locals_fitness[2].fitness(bits))
# res = det_high_climbing(bits,locals_fitness[2].fitness(bits),locals_fitness[2])
# print(res)

# print(locals_fitness[2].fitness(bits))
# res = det_high_climbing(bits, locals_fitness[2].fitness(bits), locals_fitness[2])
# print(res)
# print('\n\n')
bits = BitArray([0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1])
fitness = locals_fitness[2].fitness(bits)
ps = []
fs = []
for i in range(0, 100):
    bits = get_rand_bit_array(21)
    fitness = locals_fitness[2].fitness(bits)
    res = prob_high_climbing(bits, fitness, fitness, bits, locals_fitness[2], counter=30, aspiration=True)
    ps.append(res[0])
    fs.append(res[1])
    # print(res)
    # print('\n\n')
import matplotlib.pyplot as plt

# print(fs)
analyse_solutions(ps, '')
plt.figure()
plt.hist(fs, normed=True)
plt.show()
