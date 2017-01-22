import matplotlib.pyplot as plt
import generators as G

u_dist = G.UniformDistribution(10)
dist = G.DiscreteDistribution([1. / 2, 1. / 4, 1. / 8, 1 / 16, 1 / 16])
plt.hist(u_dist.draw(10000), alpha=0.5, label='Uniform distribution', normed=True)
plt.legend()
plt.figure()
plt.hist(dist.draw(10000, G.gen_even_dice), alpha=0.5, label='Fair Dice', normed=True)
plt.hist(dist.draw(10000, G.gen_loaded_coin), alpha=0.5, label='Loaded Coin', normed=True)
plt.hist(dist.draw(10000, G.gen_roulette), alpha=0.5, label='Roulette', normed=True)
plt.legend()

plt.show()
