import matplotlib.pyplot as plt
import numpy as np

file = open("output.txt")

n = 100
N = n+1 # including endpoints
anal = []
num = []

count = 0
for line in file:
    split_line = line.split()
    anal.append(float(split_line[0]))
    num.append(float(split_line[1]))

anal1 = np.array(anal[:N])
anal2 = np.array(anal[N:2*N])
anal3 = np.array(anal[2*N:3*N])

num1 = np.array(num[:N])
num2 = np.array(num[N:2*N]) # negative due to eigenvalue opposite of analytical; still allowed though
num3 = np.array(num[2*N:3*N])

N_list = np.linspace(0, 1, N)

plt.subplot(311)
plt.title(f"Buckling beam, n={n} steps")
plt.plot(N_list, anal1, label="Analytical")
plt.plot(N_list, num1, "--", label="Numerical")
plt.xlim(0, 1)
plt.legend()

plt.subplot(312)
plt.plot(N_list, anal2, label="Analytical")
plt.plot(N_list, num2, "--", label="Numerical")
plt.xlim(0, 1)
plt.ylabel("v(x/L)")

plt.subplot(313)
plt.plot(N_list, anal3, label="Analytical")
plt.plot(N_list, num3, "--", label="Numerical")
plt.xlim(0, 1)
plt.xlabel("x/L")

plt.subplots_adjust(hspace=0.4)
plt.savefig(f"output_{n}.pdf")
