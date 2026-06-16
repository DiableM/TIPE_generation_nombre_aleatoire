import numpy as np
import random
import math
import matplotlib.pyplot as plt

i = 0 #Numéro du fichier
nom_fichier = 'liste_nb_aleatoire_physique.txt'

liste_valeur = [] #liste des valeur lu dans le fichier

f = open(nom_fichier, 'r', encoding="latin-1")

all_line = f.readlines()
for line in all_line:
    try:
        liste_valeur.append(float(line))
        nb_point+=1
    except:
        pass


nb_barre = 75

#affiche
plt.plot()
plt.title("Distribution du générateur congruentiel")
plt.hist(liste_valeur, bins=nb_barre, range=(0,1), label = "Distribution du générateur physique")
distribution_uniforme = len(liste_valeur)/nb_barre
plt.plot([0, 1], [distribution_uniforme, distribution_uniforme], color = "red", label = "Distribution uniforme")
plt.xlabel("x")
plt.ylabel("Nombre de valeur dans l'intervalle")
plt.legend()
plt.show()

