import numpy as np
import sys
import matplotlib.pyplot as plt

path = sys.argv[1]
data = np.loadtxt(open(path, "rb"), delimiter=",")
y_tmax = list()
x_tmax = list()

for i in range(0, 10):
    x_tmax.append(data[i*5, 0])
    y_tmax.append(0)
    for j in range(0, 5):
        y_tmax[i] = data[i*5+j, -3]
    y_tmax[i] = y_tmax[i]/5
base = 50
plt.plot(x_tmax, y_tmax, label='fitness')
plt.xlabel('Tmax')
plt.ylabel('Fitness')
plt.title('Fitness VS Tmax')
plt.figure()
x_npart = list()
y_npart = list()
for i in range(0, 10):
    x_npart.append(data[i*5+base, 1])
    y_npart.append(0)
    for j in range(0, 5):
        y_npart[i] = data[i*5+j+base, -3]
    y_npart[i] = y_npart[i]/5
plt.plot(x_npart, y_npart, label='fitness')
plt.xlabel('Nb. particles')
plt.ylabel('Fitness')
plt.title('Fitness VS Nb. of particles')
plt.figure()
base = 100
x_vmax = list()
y_vmax = list()
for i in range(0, 10):
    x_vmax.append(data[i*5+base, 5])
    y_vmax.append(0)
    for j in range(0, 5):
        y_vmax[i] = data[i*5+j+base, -3]
    y_vmax[i] = y_vmax[i]/5
plt.plot(x_vmax, y_vmax, label='fitness')
plt.xlabel('Vmax')
plt.ylabel('Fitness')
plt.title('Fitness VS Vmax')
plt.figure()
base = 150
x_omg = list()
y_omg = list()
for i in range(0, 9):
    x_omg.append(data[i*5+base, 2])
    y_omg.append(0)
    for j in range(0, 5):
        y_omg[i] = data[i*5+j+base, -3]
    y_omg[i] = y_omg[i]/5
plt.plot(x_omg, y_omg, label='fitness')
plt.xlabel('omega')
plt.ylabel('Fitness')
plt.title('Fitness VS Omega')
plt.show()
