import matplotlib.pyplot as plt
import numpy as np
import re

# Fonction pour lire les données depuis un fichier
def lire_points(fichier):
    cout = []
    with open(fichier, 'r') as f:
        for line in f:
            t = line.split(";")
            t1 = t[2].split("=")
            cout.append(float(t1[1]))

    return cout

a = 3580131
b = 2766521
q = 9854547
N = 2000

z = lire_points("donnee_all.txt")
z.append(0)
print(len(z))

y = np.linspace(10**4, 10**7, N)
x = np.linspace(3*10**6, 4*10**6, N)
T = np.array(z).reshape(N, N)

X, Y = np.meshgrid(x,y)

fig = plt.figure()
ax = plt.axes(projection = "3d")
ax.plot_surface(X,Y,T.T, cmap="inferno")
ax.scatter([], [], [], color="orange", s=100, label="fonction coût")
ax.scatter([a], [b], [0], color="blue", s=100, label="minimum")

ax.legend()
ax.set_xlabel("a")
ax.set_ylabel("b")
ax.set_zlabel("coût")
ax.view_init(elev=24, azim=-68)

plt.savefig("./volume.png")
plt.show()