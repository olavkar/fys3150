import matplotlib.pyplot as plt

file = open("problem2_output.txt")

x = []
u = []
for line in file:
    x.append(float(line.split()[0]))
    u.append(float(line.split()[1]))

file.close()

plt.plot(x, u)
plt.xlabel("x")
plt.ylabel("u(x)")
plt.savefig("problem2_output.pdf")
