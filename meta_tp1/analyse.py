from scipy.stats import skewnorm, norm
import numpy as np
import matplotlib
import time


def millis():
    '''

    '''
    return int(round(time.time() * 1000))


def analyse_solutions(solutions, label=''):
    diff = []
    N = len(solutions)
    for i in range(0, N - 1):
        for j in range(i + 1, N):
            diff.append(solutions[i] - solutions[j])
    plt.hist(diff, bins=22, range=[-0.5, 21.5], color='g', alpha=0.6, normed=True)
    plt.title(label)
    plt.grid(True)
    plt.xlim(-0.5, 21.5)
    mu, sigma = norm.fit(diff)
    if sigma < 1:
        return
    a, loc, scale = skewnorm.fit(diff)
    print('  Norm Fit:')
    print('    mu:\t' + str(mu))
    print('    sigma:\t' + str(sigma))
    print('  SkewNorm Fit')
    print('    Loc:\t' + str(loc))
    print('    Scale:\t' + str(scale))
    print('    A:\t' + str(a))

    xs = np.linspace(-1, 22, 100)
    plt.plot(xs, skewnorm.pdf(xs, a, loc, scale))
    plt.plot(xs, norm.pdf(xs, mu, sigma))
    return


def analyse_fitness(fitness, label=''):
    plt.hist(fitness, label=label, color='gray', normed=True)
    plt.title(label)
    plt.grid(True)


if __name__ == '__main__':
    import matplotlib.pyplot as plt
    import random
    from NKLandscape import NKFitness, get_rand_bit_array, det_high_climbing, prob_high_climbing

    font = {'family': 'normal',
            'weight': 'normal',
            'size': 22}

    matplotlib.rc('font', **font)

    random.seed()
    N = 50
    x_plots = 2
    locals_fitness = [NKFitness(0, {0b0: 2, 0b1: 1}),
                      NKFitness(1, {0b00: 2, 0b01: 3, 0b10: 2, 0b11: 0}),
                      NKFitness(2, {0b000: 0, 0b001: 1, 0b010: 1, 0b011: 0, 0b100: 2, 0b101: 0, 0b110: 0, 0b111: 0})]
    # locals_fitness = [NKFitness(3, {0b000: 3, 0b001: 4, 0b010: 1, 0b011: 1, 0b100: 2, 0b101: 4, 0b110: 3, 0b111: 2}),
    #                   NKFitness(4, {0b000: 0, 0b001: 3, 0b010: 1, 0b011: 2, 0b100: 4, 0b101: 4, 0b110: 7, 0b111: 1}),
    #                   NKFitness(5, {0b000: 2, 0b001: 1, 0b010: 1, 0b011: 3, 0b100: 2, 0b101: 4, 0b110: 2, 0b111: 0})]

    for k in range(0, len(locals_fitness)):
        f_l = locals_fitness[k]
        solutions = []
        fitness = []
        times = []
        avg_run = 0
        print()
        t0 = millis()
        for i in range(0, N):
            x_0 = get_rand_bit_array(21)
            res = det_high_climbing(x_0, f_l.fitness(x_0), f_l)
            solutions.append(res[0])
            fitness.append(res[1])
            times.append(res[2])
            avg_run += res[2]
        t = millis() - t0
        avg_run /= 50
        print('Deterministic K ' + str(f_l.k()))
        print('  Total Time: ' + str(t) + 'ms')
        print('  Avg time: ' + str(round(t / 50)) + 'ms')
        print('  Avg nb of Step: ' + str(round(avg_run)))

        avg_run = int(round(10 * avg_run))
        plt.figure(1)
        plt.subplot(len(locals_fitness), x_plots, 1 + k * x_plots)
        analyse_solutions(solutions, 'Deterministic K' + str(f_l.k()))
        plt.figure(2)
        plt.subplot(len(locals_fitness), x_plots, 1 + k * x_plots)
        analyse_fitness(fitness, 'Deterministic K' + str(f_l.k()))

        solutions = []
        fitness = []
        print()
        t0 = millis()
        for i in range(0, N):
            x_0 = get_rand_bit_array(21)
            res = prob_high_climbing(x_0, f_l.fitness(x_0), f_l.fitness(x_0), x_0, f_l,
                                     counter=avg_run)
            solutions.append(res[0])
            fitness.append(res[1])
        t = millis() - t0
        print('Probabilistic K ' + str(f_l.k()))
        print('  Total Time: ' + str(t) + 'ms')
        print('  Avg time: ' + str(round(t / 50)) + 'ms')
        print('  Avg nb of Step: ' + str(avg_run))
        plt.figure(1)
        plt.subplot(len(locals_fitness), x_plots, 2 + k * x_plots)
        analyse_solutions(solutions, 'Probabilistic K' + str(f_l.k()))
        plt.figure(2)
        plt.subplot(len(locals_fitness), x_plots, 2 + k * x_plots)
        analyse_fitness(fitness, 'Probabilistic K' + str(f_l.k()))

    plt.show()
