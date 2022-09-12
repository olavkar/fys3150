# Plots problem 7b
import matplotlib.pyplot as plt

file1 = open("problem7b2_output.txt")
file2 = open("problem7b7_output.txt")

x1 = []
u = []
for line in file1:
    x1.append(float(line.split()[0]))
    u.append(float(line.split()[1]))

file1.close()

x2 = []
v = []
for line in file2:
    x2.append(float(line.split()[0]))
    v.append(float(line.split()[1]))

file2.close()

plt.plot(x1, u, label="u(x)"),
plt.plot(x2, v, "--", label="v(x)")
plt.plot(0, 0, label=f"n_steps={len(x1)-1}")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.legend()
plt.savefig("problem7b_output.pdf")
