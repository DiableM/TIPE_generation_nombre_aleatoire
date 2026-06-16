import numpy as np
import random
import math
import matplotlib.pyplot as plt

nom_fichier = 'liste_nb_aleatoire_physique.txt'
f = open(nom_fichier, 'r', encoding="latin-1")

contenu = f.readlines()
nb_i = 50
dx = 2/nb_i
n = 1000
nb_aleatoire = []
X = []
Y = []
D = []

for i in range(n):
    nb_aleatoire.append(float(contenu[i]))

for i in range(int(n/2)):
    X.append(nb_aleatoire[2*i])
    Y.append(nb_aleatoire[2*i+1])

for i in range(int(n/2)):
    for j in range(i+1, int(n/2)):
        D.append((X[i]-X[j])**2+(Y[i]-Y[j])**2)

nb_point_par_inter = np.zeros(nb_i+1)
for i in range(len(D)):
    nb_point_par_inter[int(D[i]/(dx))] += 1

for i in range(nb_i+1):
    nb_point_par_inter[i] = nb_point_par_inter[i]/len(D)

distribution = []
for i in range(len(nb_point_par_inter)):
    somme = 0
    for j in range(0, i):
        somme += nb_point_par_inter[j]
    distribution.append(somme)

densite = []
for i in range(len(distribution)-1):
    densite.append((distribution[i+1]-distribution[i])/dx)
densite.append(0)


x = np.linspace(0,2, nb_i+1)
y = np.zeros(nb_i+1)
dx = 2/(nb_i)
for i in range(nb_i+1):
    if i*dx<1:
        y[i] = math.pi+i*dx-4*math.sqrt(i*dx)
    if 1 <= i*dx and i*dx < 2:
        y[i] = -2 + 4*math.asin(1/math.sqrt(i*dx)) + 4*math.sqrt(i*dx-1) - math.pi - i*dx

#print(produit_scalaire(y-densite, y-densite, dx))
#print(sum(D)/len(D))

x = np.arange(0, 2+dx, dx)
plt.title("Nombre de distances par intervalle")
plt.xlabel("Intervalle I")
plt.ylabel("Effectif")
plt.bar(x[:-1], nb_point_par_inter[:-1], width=dx*0.8, align='edge')
plt.show()

plt.title("Répartition")
plt.xlabel("x")
plt.ylabel("P(X≤x)")
plt.plot(x, distribution)
plt.show()

plt.title("Densité de probabilité")
plt.xlabel("x")
plt.ylabel("Densité de probabilité")
plt.plot(x, densite)
plt.show()