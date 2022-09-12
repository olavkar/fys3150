import numpy as np
import matplotlib.pyplot as plt

n_steps = [10, 100, 1000]

for n in n_steps:
    file = open(f"problem8_{n}_output.txt")
    x = []
    u = []
    v = []

    for line in file:
        vector = line.split()
        x.append(float(vector[0]))
        u.append(float(vector[1]))
        v.append(float(vector[2]))

    x, u, v = np.array(x), np.array(u), np.array(v)

    dif_log = np.log10(abs(u - v))
    rel_dif_log = np.log10(abs((u - v)/u))

    plt.subplot(211)
    plt.title("Absolute difference")
    plt.plot(x, dif_log, label=f"n_steps={n}")
    plt.ylabel("log10(|u-v|)")

    plt.subplot(212)
    plt.title("Relative difference")
    plt.plot(x, rel_dif_log, label=f"n_steps={n}")
    plt.ylabel("log10(|u-v|/u)")

plt.xlabel("x")
#plt.legend()
plt.subplots_adjust(hspace=0.4)
plt.savefig("problem8_output.pdf")
