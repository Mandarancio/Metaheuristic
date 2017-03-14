import random as r
import fractions
import math


def lcm(a: int, b: int) -> int:
    """
    Least common multiple of 2 number
    :param a: first number
    :param b: second number
    :return: Least common multiple
    """
    return int(a * b / math.gcd(a, b))


def u_rand(n: int) -> int:
    """
    Uniform discrete random
    :param n: number of dice's faces
    :return: a random dice face
    """
    return int(r.random() * n)


class DiscreteDistribution:
    """
    Discrete Distribution class
    Manage a vector of probabilities and give basic functionality
      - Check if the sum of all the probabilities is 1
      - Compute the least common multiple of the vector of probability
    """

    def __init__(self, ps: list):
        """"
        Init the Discrete Distribution space with a vector of probabilities,
        convert it to a list of Fraction
        """
        self.__check__ = 0
        self.__ps__ = []
        for p in ps:
            self.__ps__.append(fractions.Fraction(p))
            self.__check__ += float(p)

    def prob_vector(self) -> list:
        """
        Function that return the probability vector
        :return: probability vector (list of Fraction)
        """
        return self.__ps__

    def check(self) -> bool:
        """
        Function that return if the sum of all probabilities in the probability vector is 1.0
        :return: True if sum is 1.0
        """
        return self.__check__ == 1.0

    def draw(self, n: int = 1, method=None) -> list:
        """
        Draw N events using a specified method
        :param n: number of events
        :param method: drawing function
        :return: list of integer (of size n), [-1] if no method is passed.
        """
        if method is None or not self.check():
            return [-1]
        return method(self, n)

    def get_lcm(self) -> int:
        """
        Get the least common multiple of the probability vector
        :return: the least common multiple (int) of the probability vector
        """
        multiple = self.__ps__[0].denominator

        for i in range(1, len(self.__ps__)):
            denominator = self.__ps__[i].denominator
            multiple = lcm(multiple, denominator)
        return multiple


class UniformDistribution(DiscreteDistribution):
    """
    Implementation of the uniform discrete distribution.
    """

    def __init__(self, n: int):
        """
        Initialize the probability vector with n elements with probability 1/n
        :param n: number of possible events
        """
        DiscreteDistribution.__init__(self, [])

        for i in range(0, n):
            self.__ps__.append(fractions.Fraction(1. / n))
            self.__check__ += 1. / n

    @staticmethod
    def gen_method(ps: DiscreteDistribution, n: int) -> list:
        """
        Simple method to generate n random events from a uniform discrete distribution
        :param ps: a  UniformDistribution
        :param n: number of random events to draw
        :return: list of n integer
        """
        res = []
        m = len(ps.prob_vector())
        for i in range(0, n):
            res.append(u_rand(m))
        return res

    def draw(self, n: int = 1, method=None) -> list:
        """
        Draw n events
        :param n: number of random events draw
        :param method: useless parameter (inherited from super class)
        :return: list of n integer events
        """
        return UniformDistribution.gen_method(self, n)


def gen_even_dice(distribution: DiscreteDistribution, n: int) -> list:
    """
    Generate n events of a discrete distribution using a even distribution of higher resolution
    :param distribution: discrete distribution to simulate
    :param n: number of events to draw
    :return: list of n integer events
    """
    l_lcm = distribution.get_lcm()
    # generate conversion table
    conv_table = []
    ind = 0
    for p in distribution.prob_vector():
        f_p = float(p)
        size = int(f_p / (1 / l_lcm))
        for i in range(0, size):
            conv_table.append(ind)
        ind += 1
    # generate the n events
    result = []
    for i in range(0, n):
        result.append(conv_table[u_rand(l_lcm)])

    return result


def gen_loaded_coin(distribution: DiscreteDistribution, n: int):
    """
    Generate n events of a discrete distribution using a loaded coin
    :param distribution: discrete distribution to simulate
    :param n: number of events to draw
    :return: list of n integer events
    """
    result = []
    for i in range(0, n):
        tot = 0
        ind = 0
        for p in distribution.prob_vector():
            v = r.random()
            if v <= p / (1 - tot):
                result.append(ind)
                break
            tot += p
            ind += 1
    return result


def gen_roulette(distribution: DiscreteDistribution, n: int):
    """
    Generate n events of a discrete distribution using a loaded coin
    :param distribution: discrete distribution to simulate
    :param n: number of events to draw
    :return: list of n integer events
    """
    # compute the accumulated probability of each event
    prob_cum = []
    tot = 0
    for p in distribution.prob_vector():
        prob_cum.append(tot)
        tot += p
    # generate the n events
    result = []
    for i in range(0, n):
        v = r.random()
        for j in reversed(range(0, len(prob_cum))):
            if v > prob_cum[j]:
                result.append(j)
                break
    return result
