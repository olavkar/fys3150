from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import numpy as np

B0 = 9.65*10
V0 = 2.41*10**6
d = 500
V0_d2 = V0/d**2

q = 1
m = 40.078
x0 = 20
z0 = 20
vy0 = 25
omega_z = np.sqrt(2*q*V0_d2/m)

file = open("1p_xyz_8000.txt")

x1 = []
y1 = []
z1 = []
x2 = []
y2 = []
z2 = []
t = []

for line in file:
    line = line.split()
    x1.append(float(line[0]))
    y1.append(float(line[1]))
    z1.append(float(line[2]))
    x2.append(float(line[3]))
    y2.append(float(line[4]))
    z2.append(float(line[5]))
    t.append(float(line[6]))

time = 50
n = len(t) - 1
h = time/n


# Relative error calculation
x_RK = np.transpose(np.array([x1, y1, z1]))
x_anal = np.transpose(np.array([x2, y2, z2]))

relative_error = np.zeros(len(t))
for i in range(len(t)):
    relative_error[i] = np.linalg.norm(x_anal[i] - x_RK[i])/np.linalg.norm(x_anal[i])*100

fig = plt.figure()
ax = plt.axes()
# ax = plt.axes(projection="3d")
ax.set_title(f"Relative error, stepsize $h={h}\mu s$")
#ax.plot3D(x1, y1, z1, label="Particle 1")
#ax.plot3D(x2, y2, z2, label="Particle 2")
ax.plot(t, relative_error)
#ax.plot(x2, y2, "--", label="Particle 2")

ax.set_xlabel("t $[\mu s]$")
ax.set_ylabel("% error")
#ax.set_zlabel("z $[\mu m]$")
#ax.set_xlim(t[0], t[-1])
#ax.legend()
#plt.axis("equal")

#ax.set_xlim3d(left=-500, right=500)
#ax.set_ylim3d(bottom=-500, top=500)
#ax.set_zlim3d(bottom=-500, top=500)
plt.savefig("1p_xyz_8000.pdf")
