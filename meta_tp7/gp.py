import random
import sys
import matplotlib.pyplot as plt
import numpy as np
import time

def printProg(prog):
    s = prog[0].__name__
    for i in range(1, len(prog)):
        s += ' ' + prog[i].__name__
    print(s)


# This is the machine on which programs are executed
# The output is the value on top of the pile.
class CPU:
    def __init__(self):
        self.stack = []

    def reset(self):
        while len(self.stack) > 0:
            self.stack.pop()

    def size(self):
        return len(self.stack)

    def pop(self):
        if self.size() == 0:
            return -10000
        return self.stack.pop()

    def push(self, v):
        return self.stack.append(v)


# These are the instructions
def AND(cpu, data):
    if cpu.size() >= 2:
        v1 = cpu.pop()
        v2 = cpu.pop()
        cpu.push(bool(v1 and v2))
        return 0
    return 1


def OR(cpu, data):
    if cpu.size() >= 2:
        v1 = cpu.pop()
        v2 = cpu.pop()
        cpu.push(bool(v1 or v2))
        return 0
    return 1


def XOR(cpu, data):
    if cpu.size() >= 2:
        v1 = cpu.pop()
        v2 = cpu.pop()
        cpu.push(bool(v1) ^ bool(v2))
        return 0
    return 1


def NOT(cpu, data):
    if cpu.size() >= 1:
        v1 = cpu.pop()
        cpu.push(bool(not v1))
        return 0
    return 1


# Push values of variables on the stack.
def X1(cpu, data):
    cpu.push(bool(data[0]))
    return 0


def X2(cpu, data):
    cpu.push(bool(data[1]))
    return 0


def X3(cpu, data):
    cpu.push(bool(data[2]))
    return 0


def X4(cpu, data):
    cpu.push(bool(data[3]))
    return 0


def T(cpu, dat):
    cpu.push(True)
    return 0


def F(cpu, dat):
    cpu.push(False)
    return 0


# Execute a program
def execute(program, cpu, data):
    cpu.reset()
    errors = 0
    for p in program:
        errors += p(cpu, data)
    v = cpu.pop()
    errors += cpu.size()
    return v, errors


# Generate a random program
def randomProg(length, functionSet, terminalSet):
    prog = []
    nT = len(terminalSet)-1
    nF = len(functionSet)-1
    for i in range(0, length):
        if random.random() < 0.5:
            prog.append(terminalSet[random.randint(0, nT)])
        else:
            prog.append(functionSet[random.randint(0, nF)])
    return prog


# Computes the fitness of a program.
# The fitness counts how many instances of data in dataSet are correctly
# computed by the program
def computeFitness(prog, cpu, dataSet):
    f = 0
    err = 0
    for data in dataSet:
        r = data[4]
        ff, ee = execute(prog, cpu, data)
        err += ee
        f += int(r == ff)
    if (err>0):
        return (f-len(dataSet))*2
    return (f-len(dataSet))#*(1+err)


# Compute the fitness of all programs
def computeAllFitness(Population, cpu, dataSet):
    listOfFitness = []
    for i in range(len(Population)):
        prog = Population[i]
        f = computeFitness(prog, cpu, dataSet)
        listOfFitness.append((i, f))
    return listOfFitness


def best(fitness):
    b = fitness[0][1]
    ind = fitness[0][0]
    for i in range(1, len(fitness)):
        if fitness[i][1] > b:
            ind = fitness[i][0]
    return ind


def worst(fitness):
    b = fitness[0]
    ind = 0
    for i in range(1, len(fitness)):
        if fitness[i] < b:
            ind = i
    return ind


# Selection using 2-tournament.
def selection(Population, listOfFitness):
    newPopulation = []
    n = len(Population)
    for i in range(n):
        i1 = random.randint(0, n-1)
        i2 = random.randint(0, n-1)
        if listOfFitness[i1][1] > listOfFitness[i2][1]:
            newPopulation.append(Population[i1])
        else:
            newPopulation.append(Population[i2])
    return newPopulation


def crossover(Population, p_c):
    newPopulation = []
    n = len(Population)
    i = 0
    while(i < n):
        p1 = Population[i]
        p2 = Population[(i+1) % n]
        m = len(p1)
        if random.random() < p_c:  # crossover
            k = random.randint(1, m-1)
            newP1 = p1[0:k]+p2[k:m]
            newP2 = p2[0:k]+p1[k:m]
            p1 = newP1
            p2 = newP2
        newPopulation.append(p1)
        newPopulation.append(p2)
        i += 2
    return newPopulation


def mutation(Population, p_m, terminalSet, functionSet):
    newPopulation = []
    nT = len(terminalSet)-1
    nF = len(functionSet)-1
    for p in Population:
        for i in range(len(p)):
            if random.random() > p_m:
                continue
            if random.random() < 0.5:
                p[i] = terminalSet[random.randint(0, nT)]
            else:
                p[i] = functionSet[random.randint(0, nF)]
        newPopulation.append(p)
    return newPopulation

# -------------------------------------

# LOOK-UP TABLE YOU HAVE TO REPRODUCE.
nbVar = 4
dataSet = [[0, 0, 0, 0, 0], [0, 0, 0, 1, 1], [0, 0, 1, 0, 0], [0, 0, 1, 1, 0],
           [0, 1, 0, 0, 0], [0, 1, 0, 1, 0], [0, 1, 1, 0, 0], [0, 1, 1, 1, 1],
           [1, 0, 0, 0, 0], [1, 0, 0, 1, 1], [1, 0, 1, 0, 0], [1, 0, 1, 1, 0],
           [1, 1, 0, 0, 0], [1, 1, 0, 1, 0], [1, 1, 1, 0, 0], [1, 1, 1, 1, 0]]

# Example of program.
# prog = [X3, X2, XOR, NOT, X1, X2, AND, X3, XOR, X4, AND]
# prog = [X3, X2, XOR, NOT, X1, X2, AND, X3, AND, XOR, X4, AND]
# x4 and ((x3 and x2) xor (x1 and x2 and x3))
# printProg(prog)
# print("Program Size: "+str(len(prog)))

cpu = CPU()
functionSet = [AND, OR, NOT, XOR]
terminalSet = [X1, X2, X3, X4]


def run(pm=0.1, pc=0.6, pop=100, gmax=500, l=10):
    # to be checked
    popSize = pop
    p_c = pc
    p_m = pm

    # Generate the initial population
    # Evolution. Loop on the creation of population at generation i+1 from
    # population at generation i, through selection, crossover and mutation.

    population = []
    progLength = l
    # 11
    # X3 X1 AND X4 NOT OR X2 X3 XOR OR NOT

    for i in range(0, popSize):
        prog = randomProg(progLength, functionSet, terminalSet)
        population.append(prog)
    fitness = computeAllFitness(population, cpu, dataSet)
    for g in range(0, gmax):
        ind = best(fitness)
        f = fitness[ind][1]
        best_individual = population[ind][:]
        population = selection(population, fitness)
        population = crossover(population, p_c)
        population = mutation(population, p_m, terminalSet, functionSet)
        fitness = computeAllFitness(population, cpu, dataSet)
        w = worst(fitness)
        population[w] = best_individual
        fitness[w] = (w, f)
    ind = best(fitness)
    best_individual = population[ind][:]
    f = fitness[ind][1]
    return f, best_individual


fs = []
bf = -1000
bi = []
gmax = 100
pop = 100
millis = int(round(time.time() * 1000))
for i in range(0, 100):
    sys.stdout.write("\r["+str(i+1)+"/100]")
    sys.stdout.flush()
    f, ind = run(gmax=gmax, pop=pop, pm=0.5, pc=0.2, l=10)
    if f > bf:
        bf = f
        bi = ind
    fs.append(f)
print()
plt.plot(fs)
millis = int(round(time.time() * 1000))-millis

print("N eval: "+str(gmax*pop))
print("Best Fitness: "+str(bf))
print("Mean: "+str(np.mean(fs)))
print("Std: "+str(np.std(fs)))
print("Time: "+str(millis/100))
printProg(bi)
plt.show()
