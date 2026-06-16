import numpy as np
import random
import math
import matplotlib.pyplot as plt

nom_fichier = 'liste_nb_aleatoire_physique.txt'
f = open(nom_fichier, 'r', encoding="latin-1")

def produit_scalaire(X, Y, dx):
    v = 0
    for i in range(0, len(X)):
        v += X[i]*Y[i]*dx
    return v

contenu = f.readlines()
liste_nb_aleatoire = []
for line in contenu:
    liste_nb_aleatoire.append(float(line))

X = []
Y = []
for i in range(0, len(liste_nb_aleatoire)-1, 2):
    X.append(liste_nb_aleatoire[i])
    Y.append(liste_nb_aleatoire[i+1])

n = len(X)
D = []
for i in range(n):
    for j in range(i+1, n):
        D.append((X[i]-X[j])**2+(Y[i]-Y[j])**2)

t = []
I = []
nb_i = 5
d_tot = 2
dt = d_tot/nb_i

for i in range(nb_i+1):
    t.append(i*dt)
    I.append(0)

jarod = 0
next_jarod = len(D)/10
next_jarod_i = 0

for i in range(len(D)):
    j = 0
    while D[i] > t[j]:
        j += 1
    I[j-1] += 1
    jarod += 1
    if jarod == next_jarod:
        next_jarod_i += 1
        next_jarod = next_jarod + len(D)/10
        #print(next_jarod_i)
    
for i in range(nb_i+1):
    I[i] = I[i]/len(D)


distribution = []
for i in range(len(I)):
    somme = 0
    for j in range(0, i):
        somme += I[j]
    distribution.append(somme)
    
densite = []
for i in range(len(distribution)-1):
    densite.append((distribution[i+1]-distribution[i])/dt)
densite.append(0)

for i in range(len(distribution)):
    print("distribution", distribution[i])

for i in range(len(densite)):
    print("densiter", densite[i])

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

plt.plot(t, densite)
plt.plot(x, y, 'red')
plt.show()