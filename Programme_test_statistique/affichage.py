import numpy as np
import random
import math
import matplotlib.pyplot as plt

def produit_scalaire(X, Y, dx):
    v = 0
    for i in range(0, len(X)):
        v += X[i]*Y[i]*dx
    return v

nom_fichier_congruentiel = 'Donnee/Donnee_test_densite/g_congruentiel.txt'
nom_fichier_congruentiel_mauvais = 'Donnee/Donnee_test_densite/g_congruentiel_mauvais.txt'
nom_fichier_logistique = 'Donnee/Donnee_test_densite/g_logistique.txt'
nom_fichier_physique = 'Donnee/Donnee_test_densite/g_physique.txt'

f1 = open(nom_fichier_congruentiel, 'r', encoding="latin-1")
f2 = open(nom_fichier_logistique, 'r', encoding="latin-1")
f3 = open(nom_fichier_physique, 'r', encoding="latin-1")
f4 = open(nom_fichier_congruentiel_mauvais, 'r', encoding="latin-1")


lines1 = f1.readlines()
lines2 = f2.readlines()
lines3 = f3.readlines()
lines4 = f4.readlines()

Y1 = []
Y2 = []
Y3 = []
Y4 = []

for l in lines1:
    Y1.append(float(l))
for l in lines2:
    Y2.append(float(l))
for l in lines3:
    Y3.append(float(l))
for l in lines4:
    Y4.append(float(l))



nb_i = len(Y1)-1
x = np.linspace(0,2, nb_i+1)
y = np.zeros(nb_i+1)
dx = 2/(nb_i)
for i in range(nb_i+1):
    if i*dx<1:
        y[i] = math.pi+i*dx-4*math.sqrt(i*dx)
    if 1 <= i*dx and i*dx < 2:
        y[i] = -2 + 4*math.asin(1/math.sqrt(i*dx)) + 4*math.sqrt(i*dx-1) - math.pi - i*dx

plt.xlabel("x")
plt.ylabel("Densité")
plt.title("Comparaison entre les générateurs")
plt.plot(x, Y1, label="Congruentiel")
plt.plot(x, Y2, label="Logistique")
plt.plot(x, Y3, label="Physique")
#plt.plot(x, Y4, label="Congruentiel mauvais")
plt.plot(x, y, 'red', label="Théorique")
plt.legend()

plt.show()

print("Congruentiel = ", produit_scalaire(Y1-y, Y1-y, dx))
print("Congruentiel mauvais = ", produit_scalaire(Y4-y, Y4-y, dx))
print("Logistique = ", produit_scalaire(Y2-y, Y2-y, dx))
print("Physique = ", produit_scalaire(Y3-y, Y3-y, dx))

d1 = produit_scalaire(Y1-y, Y1-y, dx)
d2 = produit_scalaire(Y2-y, Y2-y, dx)
d3 = produit_scalaire(Y3-y, Y3-y, dx)
d4 = produit_scalaire(Y4-y, Y4-y, dx)

d1 = 0.00071
d2 = 0.000049
d3 = 0.079
d4 = 5.94

label = ["Congruentiel", "Logistique", "Physique", "Congruentiel mauvais"]
y_histo = [d1, d2, d3, d4]
x_histo = np.arange(len(label))

plt.title("Comparaison entre les générateurs")
plt.ylabel("Distance au carré")
plt.stem(x_histo, y_histo)
plt.xticks(x_histo, label, rotation=45, ha='right')
plt.tight_layout()

plt.show()

