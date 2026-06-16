import numpy as np
import random
import math
import matplotlib.pyplot as plt

nom_fichier = 'liste_nb_aleatoire_physique.txt'
#nom_fichier = 'liste_nb_suite_logistique.txt'


def exposant(x, y):
    return np.exp(y*np.log(x))

liste_nb_aleatoire = np.loadtxt(nom_fichier , encoding="latin-1")

n = 1000
dx = 1/n
x_th = np.linspace(0,1, n)
y_th = np.full(n, 1/n)

x = np.linspace(0, 1, n)
y, _ = np.histogram(liste_nb_aleatoire, bins=n, range=(0, 1))
y = y / len(liste_nb_aleatoire)

z_th = np.zeros_like(y)
z_th[1:] = np.cumsum(y[1:])
#P = np.polyfit(x_th, z_th, 1)
#a_th = np.polyval(P, x_th)

"""
g = open("valeur_logistique.txt", 'w')
g.write("P = ")
for i in range(len(P)-1):
    g.write("{}X**{} +".format(P[i], len(P)-i-1))
g.write("{}\n".format(P[len(P)-1]))
g.write("[")
for i in range(len(P)-1):
    g.write("{}, ".format(P[i]))
g.write("{}]\n".format(P[len(P)-1]))
g.close
"""
#b_th = np.polyval(P, liste_nb_aleatoire)
d_th = (2/(np.pi))*np.arcsin(np.sqrt(x))

#c, _ = np.histogram(b_th, bins=n, range=(0, 1))
#c = c / len(b_th)

jarod = (2/(np.pi))*np.arcsin(np.sqrt(liste_nb_aleatoire))
e, _ = np.histogram(jarod, bins=n, range=(0, 1))
e = e / len(liste_nb_aleatoire)

with open("sortie_bin.bin", "wb") as f:
    for i in range(len(jarod)):
        f.write(int(jarod[i]).to_bytes(4, "little"))

plt.plot()
plt.step(x, y)
plt.plot(x_th, y_th, 'red')
#plt.step(x, c)
plt.step(x, e, 'green')
plt.savefig("fig1.png", dpi=1000, bbox_inches="tight")
plt.show()

plt.plot()
plt.plot(x_th, z_th, 'green')
#plt.plot(x_th, a_th, 'purple')
plt.plot(x_th, d_th, 'red')
plt.savefig("fig2.png", dpi=1000, bbox_inches="tight")
plt.show()
