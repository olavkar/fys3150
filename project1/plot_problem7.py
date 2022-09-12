# Plots problem 7a
import matplotlib.pyplot as plt

file = open("problem7_output.txt")

x = []
v = []
for line in file:
    x.append(float(line.split()[0]))
    v.append(float(line.split()[1]))

file.close()

plt.plot(x, v)
plt.xlabel("x")
plt.ylabel("v(x)")
plt.savefig("problem7_output.pdf")
