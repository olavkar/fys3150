import numpy as np
import matplotlib.pyplot as plt

n_steps = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
max_eps = np.zeros(len(n_steps))

for i in range(len(n_steps)):
    file = open(f"problem8_{n_steps[i]}_output.txt")
    x = []
    u = []
    v = []

    for line in file:
        vector = line.split()
        x.append(float(vector[0]))
        u.append(float(vector[1]))
        v.append(float(vector[2]))

    x, u, v = np.array(x), np.array(u), np.array(v)

    rel_dif_log = np.log10(abs((u - v)/u))

    max_eps[i] = np.amax(rel_dif_log)

    plt.plot(x, rel_dif_log, label=f"{np.log10(n_steps[i])}")

print(max_eps)
plt.xlabel("x")
plt.ylabel("log10(epsilon_i)")
plt.legend()
plt.savefig("problem8c_output.pdf")
