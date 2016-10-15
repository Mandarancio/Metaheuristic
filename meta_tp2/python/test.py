import QAP
import tp_import as tpi
n,D,W=tpi.import_dat('1.dat')
I = QAP.QAP(n,D,W)
# xs=[QAP.rand_solution(n)]
# xs=[QAP.Solution([12,11,10,9,8,7,6,5,4,3,2,1]),QAP.Solution([1,12,11,10,9,8,7,6,5,4,3,2]),QAP.Solution([1,2,3,4,5,6,7,8,9,10,11,12])]
xs=[]
xx=[]#[xs[0].to_int(),xs[1].to_int()]
ys=[]#[I.fitness(xs[0]),I.fitness(xs[1])]
yy=[]
t = QAP.rand_solution(n).objects()
my = []
# for i in range(0,n):
    # t.append(i+1)

for i in range(0,n+1):
    s= QAP.Solution(t)
    yy.append(I.fitness(s))
    y = 0
    myy= yy[-1]
    xs.append(s)
    y+=I.fitness(s)
    ns = s.neighbors()
    T = 1+len(ns)
    for x in ns:
        xs.append(x)
        f = I.fitness(xs[-1])
        if f<myy:
            myy=f
        y += f

    tt = [t[n-1]]
    tt.extend(t[:-1])
    t=tt
    my.append(myy)
    ys.append(y/T)
# for i in range(1,1000):
    # xs.append(xs[i-1].rand_neighbor())
    # ys.append(I.fitness(xs[i]))
import matplotlib.pyplot as plt
import numpy as np
print(np.min(ys))
plt.plot(ys)
plt.plot(yy)
plt.plot(my)

# plt.figure()
# plt.hist(ys,bins=50,normed=True,alpha=0.6)
plt.show()
