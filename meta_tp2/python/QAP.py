import random
import sys

random.seed()
sys.setrecursionlimit(20000)


class Solution:
    def __init__(self, objects: list):
        self.__objects__ = objects
        self.__n__ = len(objects)

    def objects(self):
        return self.__objects__

    def n(self):
        return self.__n__

    def psi(self, i: int):
        return self.__objects__.index(i + 1)

    def neighbors(self):
        ns = []
        for i in range(0, self.__n__ - 1):
            for j in range(i + 1, self.__n__):
                n = self.__objects__[:]
                n[i] = self.__objects__[j]
                n[j] = self.__objects__[i]
                ns.append(Solution(n))
        return ns

    def to_int(self):
        t = 0
        for i in range(0, self.__n__):
            t += self.__objects__[i]*(i+1)
        return t

    def neighbor(self, i: int, j: int):
        n = self.__objects__[:]
        n[i] = self.__objects__[j]
        n[j] = self.__objects__[i]
        return Solution(n)

    def rand_neighbor(self):
        i = random.randint(0, self.__n__-1)
        j = random.randint(0, self.__n__-1)
        while i == j:
            j = random.randint(0, self.__n__-1)
        return self.neighbor(i, j)

    def __repr__(self):
        return str(self.__objects__)

    def __getitem__(self, i):
        return self.__objects__[i]


def rand_solution(n: int):
    sol = []
    for i in range(0, n):
        sol.append(i+1)
    sol = Solution(sol)
    for i in range(0, n):
        x = random.randint(0, n-1)
        y = random.randint(0, n-1)
        sol = sol.neighbor(x, y)
    return sol


class TabuMatrix:
    def __init__(self, n: int, st_length: int):
        self.__l__ = st_length
        self.__st_matrix__ = []
        self.__n__ = n
        self.__max_history__ = n*n
        self.__t__ = 1
        self.__diversification__ = True
        for i in range(0, n):
            self.__st_matrix__.append([])
            for j in range(0, n):
                self.__st_matrix__[i].append(0)

    def set_diversification(self, div: bool):
        self.__diversification__ = div

    def step(self):
        self.__t__ += 1

    def status(self, n: int, j: int):
        return self.__t__ > self.__st_matrix__[n-1][j]

    def is_mandatory(self, s: Solution, i: int, j: int):
        if not self.__diversification__:
            return False

        ti = self.__st_matrix__[s[i]-1][j]+self.__max_history__
        tj = self.__st_matrix__[s[j]-1][i]+self.__max_history__
        return self.__t__ > ti+self.__l__ and self.__t__ > tj+self.__l__

    def tabu(self, s: Solution, i: int, j: int):
        t = self.__t__
        self.__t__ += 1
        self.__st_matrix__[s[i]-1][i] = t+self.__l__
        self.__st_matrix__[s[j]-1][j] = t+self.__l__

    def t(self):
        return self.__t__

    def __repr__(self):
        s = '\nShort term\n'
        for i in range(0, self.__n__+2):
            for j in range(0, self.__n__+1):
                if i < 2 and j < 1:
                    s += '  '
                elif i == 0 and j > 0:
                    s += ' '+str(j)+' '
                elif i == 1 and j > 0:
                    s += '___'
                elif i > 1 and j == 0:
                    s += str(i-1)+'|'
                elif i > 1 and j > 0:
                    s += ' '+str(self.__st_matrix__[i-2][j-1])+' '
            s += '\n'

        return s


class QAP:
    def __init__(self, n: int, D: list, W: list, tabu_length: int=10):
        self.__n__ = n
        self.__w__ = W
        self.__d__ = D
        self.__tabu__ = TabuMatrix(n, tabu_length)
        self.__l__ = tabu_length
        self.__is__ = []

    def tabu(self):
        return self.__

    def n(self):
        return self.__n__

    def d(self):
        return self.__d__

    def w(self):
        return self.__w__

    def reset(self):
        self.__tabu__ = TabuMatrix(self.__n__, self.__l__)
        self.__is__ = []

    def Is(self):
        return self.__is__

    def fitness(self, s: Solution):
        I = 0
        n = s.n()
        for i in range(0, n):
            di = s.psi(i)
            for j in range(i+1, n):
                w = self.__w__[i][j]
                dj = s.psi(j)
                d = self.__d__[di][dj]
                I += w * d
        return 2*I

    def delta_fitness(self, s: Solution, i: int, j: int):
        delta = 0
        si = s[i]-1
        sj = s[j]-1
        di = i
        dj = j
        for k in range(0, s.n()):
            if k == si or k == sj:
                continue
            dk = s.psi(k)
            dd = (self.__w__[k][si]-self.__w__[k][sj])*(self.__d__[dk][di]-self.__d__[dk][dj])
            delta += dd
        return 2*delta

    def __step_U__(self, s: Solution, current_fitness: int, best_fitness: int):
        min_n = None
        min_f = sys.maxsize
        perm = [-1, -1]
        mandatory = False
        for i in range(0, s.n()-1):
            for j in range(i+1, s.n()):
                f = current_fitness-self.delta_fitness(s, i, j)
                t_mandatory = self.__tabu__.is_mandatory(s, i, j)
                if f < min_f and f < best_fitness:
                    min_f = f
                    perm = [i, j]
                elif min_f >= best_fitness:
                    if (t_mandatory or mandatory):
                        if not mandatory or (f < min_f and t_mandatory):
                            mandatory = True
                            min_f = f
                            perm = [i, j]
                    elif self.__tabu__.status(s[i], j) and self.__tabu__.status(s[j], i):
                        if f < min_f:
                            # min_n =s.neighbor(i,j)
                            min_f = f
                            perm = [i, j]
        if perm[0] < 0:
            self.__tabu__.step()
            return s, current_fitness
        min_n = s.neighbor(perm[0], perm[1])
        self.__tabu__.tabu(s, perm[0], perm[1])
        return min_n, min_f

    def U(self, s0: Solution, iterations: int=1000, div: bool=True):
        s = s0
        f = self.fitness(s0)
        best_f = f
        best_n = s0
        self.__tabu__.set_diversification(div)
        for i in range(0, iterations):
            s, f = self.__step_U__(s, f, best_f)
            self.__is__.append(f)
            if f < best_f:
                best_f = f
                best_n = s
        return best_n, best_f


def find_first_solution(I: QAP):
    n = I.n()
    s = rand_solution(n)
    fmin = I.fitness(s)
    init = s
    for i in range(0, n+1):
        f = I.fitness(s)
        if f < fmin:
            fmin = f
            init = s
        ns = s.neighbors()
        for x in ns:
            f = I.fitness(x)
            if f < fmin:
                fmin = f
                init = x
        t = s.objects()
        tt = [t[n-1]]
        tt.extend(t[:-1])
        s = Solution(tt)
    return init
