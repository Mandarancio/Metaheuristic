import NKLandscape as NKL
import random

random.seed()

# locals_fitness = [NKL.NKFitness(0, {0b0: 2, 0b1: 1}),
#                   NKL.NKFitness(1, {0b00: 2, 0b01: 3, 0b10: 2, 0b11: 0}),
#                   NKL.NKFitness(2, {0b000: 0, 0b001: 1, 0b010: 1, 0b011: 0, 0b100: 2, 0b101: 0, 0b110: 0, 0b111: 0})]
locals_fitness = [NKL.NKFitness(3, {0b0: 2, 0b1: 1}),
                  NKL.NKFitness(1, {0b00: 2, 0b01: 3, 0b10: 2, 0b11: 0}),
                  NKL.NKFitness(2, {0b000: 0, 0b001: 1, 0b010: 1, 0b011: 0, 0b100: 2, 0b101: 0, 0b110: 0, 0b111: 0})]

print('NK Landscape (TP1)')
print('N: 21\n-----\n')
K=''
N=21
while not K in ['0','1','2']:
    K = input('Chose the K (0-2): ')
    if not K in ['0','1','2']:
        print('Option "'+K+'" not valid, please try again')
algorithm = ''
print('')
while not algorithm in ['1','2']:
    algorithm=input('1. Deterministic High-Climbing\n2. Probabilistic High-Climbing\nChose the method (1-2): ')
    if  not algorithm in ['1','2']:
        print('Option "'+algorithm+'" not valid, please try again')
K=int(K)

local_fitness = locals_fitness[K]
bits = NKL.get_rand_bit_array(N)
fit = local_fitness.fitness(bits)
print('\nStarting sequence: '+str(bits)+'\n......')
if algorithm=='1':
    res = NKL.det_high_climbing(bits,fit,local_fitness)
else:
    res = NKL.prob_high_climbing(bits,fit,fit,bits,local_fitness,50)
print(str(res[0])+' : '+str(res[1]))
