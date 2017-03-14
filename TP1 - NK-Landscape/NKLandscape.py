from random import random


class BitArray:
    '''
    Class to represent a bit sequence
    '''

    def __init__(self, bit_array: list):
        '''
        Initialize the bit sequence
        :param bit_array: list of boolean (bits)
        '''
        self.__bit_array__ = []
        for b in bit_array:
            self.__bit_array__.append(bool(b))
        self.__length__ = len(bit_array)
        self.__value__ = self.__value__()

    def __value__(self) -> int:
        '''
        Compute decimal value of the sequence
        :return: decimal value
        '''
        v = 0
        for i in range(0, len(self.__bit_array__)):
            v += int(self.__bit_array__[i]) * (2 ** (self.__length__ - 1 - i))
        return v

    def bits(self) -> list:
        '''
        Get the binary sequence
        :return: list of bits
        '''
        return self.__bit_array__

    def value(self) -> int:
        '''
        Get the decimal value of the sequence
        :return: integer value
        '''
        return self.__value__

    def size(self) -> int:
        '''
        Get the number of bits in the sequence
        :return: the number of bits in the sequence
        '''
        return self.__length__

    def neighbors(self) -> list:
        '''
        Compute the neighbors of the sequence (all the sequences with Hamming distance of 1)
        :return: list of neighbors (BitArray)
        '''
        neighbors = []
        for i in range(0, self.__length__):
            neighbor = self.__bit_array__[:]
            neighbor[i] = not neighbor[i]
            neighbors.append(BitArray(neighbor))
        return neighbors

    @staticmethod
    def from_string(bits: str):
        '''
        Generate a BitArray from a string
        :param bits: string of bit (010001)
        :return: the BitArray
        '''
        arr = []
        for i in range(0, len(bits)):
            arr.append(bits[i] == '1')
        return BitArray(arr)

    @staticmethod
    def from_number(num: int):
        '''
        Generate a BitArray from a number
        :param num: integer number
        :return: BitArray
        '''
        return BitArray.from_string(bin(num)[2:])

    def __repr__(self):
        s = '0b'
        mod = 4 - self.__length__ % 4
        if mod == 4:
            mod = 0
        for i in range(0, mod):
            s += 'x'
        for i in range(0, self.__length__):
            if (i + mod) % 4 == 0 and mod + i > 0:
                s += ' '
            s += str(int(self.__bit_array__[i]))
        return s

    def __int__(self):
        return self.__value__

    def __float__(self):
        return float(self.__value__)

    def __getitem__(self, index):
        if -1 < index < self.__length__:
            return self.__bit_array__[index]
        return -1

    def __lt__(self, other):
        return self.__value__ < other

    def ___le__(self, other):
        return self.__value__ <= other

    def __eq__(self, other):
        return self.__value__ == other

    def __ne__(self, other):
        return self.__value__ != other

    def __gt__(self, other):
        return self.__value__ > other

    def __ge__(self, other):
        return self.__value__ >= other

    def __sub__(self, other):
        '''
        Compute the Hamming distance between 2 BitArrays
        :param other: BitArray
        :return: Hamming distance (integer)
        '''
        if type(other) is BitArray:
            l1 = self.__length__
            l2 = other.size()
            i1 = 0 if l1 < l2 else l1 - l2
            i2 = 0 if l2 < l1 else l2 - l1
            dif = abs(l1 - l2)
            for i in range(0, l1 if l1 < l2 else l2):
                dif += 1 * (int(self[i + i1] ^ other[i + i2]))
            return dif
        return -1


def get_rand_bit_array(N: int) -> BitArray:
    '''
    Generate a random sequence of N bits
    :param N: number of bits
    :return: a random BitArray
    '''
    bit_array = []
    for i in range(0, N):
        bit_array.append(1 if random() > 0.5 else 0)
    return BitArray(bit_array)


class NKFitness:
    '''
    Class to manage and compute of a NK Landscape fitness
    '''

    def __init__(self, K: int, local_fitness: dict):
        '''
        Initialize the object, with the K of the landscape and the local fitness
        :param K: K of the landscape
        :param local_fitness: A map with the values of the local fitness
        '''
        self.__K__ = K
        self.__local_fitness__ = local_fitness

    def fitness(self, x: BitArray) -> int:
        '''
        Compute the fitness of a BitArray
        :param x: sequence
        :return: fitness value (integer)
        '''
        if x.size() == self.__K__ + 1:
            if x.value() in self.__local_fitness__:
                return self.__local_fitness__[x.value()]
            return 0

        fitness = 0
        N = x.size()
        K = self.__K__ + 1
        for i in range(0, N - self.__K__):
            sub_bits = BitArray(x.bits()[i:i + K])
            val = self.fitness(sub_bits)
            fitness += val
        return fitness

    def k(self) -> int:
        '''
        Get the K of the landscape
        :return: K of the landscape (integer)
        '''
        return self.__K__


def det_high_climbing(x_i: BitArray, current_fitness: int, fitness_function: NKFitness, counter: int = 0) -> list:
    '''
    Deterministic High-Climbing Meta-Heuristic, choose the neighbor with highest fitness if higher of the fitness of
     the current sequence.

    :param x_i: Current sequence
    :param current_fitness: Current fitness value
    :param fitness_function: Fitness function
    :param counter: Counter of the steps did to find the solution
    :return: found sequence, fitness value, steps done
    '''
    neighbors = x_i.neighbors()
    max_v = current_fitness
    max_ind = -1
    for i in range(0, len(neighbors)):
        fitness = fitness_function.fitness(neighbors[i])
        if fitness > max_v:
            max_ind = i
            max_v = fitness
    if max_ind < 0:
        return x_i, current_fitness, counter
    else:
        return det_high_climbing(neighbors[max_ind], max_v, fitness_function, counter + 1)


def 	prob_high_climbing(x_i: BitArray, fitness_i: int, max_fitness: int, max_x: BitArray,
                       fitness_function: NKFitness, counter: int = 50) -> list:
    '''
    Probabilistic High-Climbing with aspiration Meta-Heuristic. Choose the neighbor with fitness higher of the maximum ever found
    otherwise chose a random neighbor (with a loaded dice) till the counter is greater then 0

    :param x_i: current sequence
    :param fitness_i: current fitness
    :param max_fitness: highest ever find fitness
    :param max_x: sequence associated to the highest fitness
    :param fitness_function: Fitness function
    :param counter: countdown counter to stop the meta
    :return: found sequence, fitness value
    '''

    if (counter < 0):
        return max_x, max_fitness
    neighbors = x_i.neighbors()
    tot_v = 0
    probabilities = []
    max_v = max_fitness
    max_n = None
    for n in neighbors:
        l_f = fitness_function.fitness(n)
        tot_v += l_f
        probabilities.append(l_f)
        if l_f > max_v:
            max_n = n
            max_v = l_f

    if max_n is not None:
        return prob_high_climbing(max_n, max_v, max_v, max_n, fitness_function, counter - 1)

    r = random()
    p_cum = 0

    for i in range(0, len(probabilities)):
        if p_cum < r < p_cum + probabilities[i] / tot_v:
            return prob_high_climbing(neighbors[i], probabilities[i], max_fitness, max_x, fitness_function,
                                      counter - 1)
        p_cum += (probabilities[i] / tot_v)
