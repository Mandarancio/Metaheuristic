import numpy as np
import sys
import matplotlib.pyplot as plt

path = sys.argv[1]
data = np.loadtxt(open(path, "rb"), delimiter=",")
fs = data[:, -3]
ps = 1-data[:, -2]
xmax = len(fs)
fs_mean = np.mean(fs)
fs_std = np.std(fs)
plt.plot(fs, "bx-", label="fitness")
plt.plot([0, xmax], [fs_mean, fs_mean], "r--", label="mean")
plt.plot([0, xmax], [fs_mean+fs_std, fs_mean+fs_std], 'g--', label="std")
plt.plot([0, xmax], [fs_mean-fs_std, fs_mean-fs_std], 'g--')
# plt.plot(ps, "gx-", label="Precision")
print("FITNESS")
print("mean: "+str(fs_mean))
print("std: "+str(fs_std))
print("best: "+str(np.min(fs)))

# plt.xlim([0, xmax])
plt.legend()
plt.xlabel("Iterations")
plt.ylabel("Fitness")
plt.xlim([0, xmax-1])
plt.title("Fitness")
plt.figure()

ps_mean = np.mean(ps)
ps_std = np.std(ps)
plt.plot(ps, "bx-", label="error")
plt.plot([0, xmax], [ps_mean, ps_mean], "r--", label="mean")
plt.plot([0, xmax], [ps_mean+ps_std, ps_mean+ps_std], 'g--', label="std")
plt.plot([0, xmax], [ps_mean-fs_std, ps_mean-ps_std], 'g--')
# plt.plot(ps, "gx-", label="Precision")
print("PREDICTED ERROR")
print("mean: "+str(ps_mean))
print("std: "+str(ps_std))
print("best: "+str(np.min(ps)))
plt.legend()
plt.xlabel("Iterations")
plt.ylabel("Predicted Error")
plt.xlim([0, xmax-1])
plt.title("Predicted Error")
plt.show()
