import numpy as np
import random
import math
import matplotlib.pyplot as plt

i = 0 #Numéro du fichier
nom_fichier = 'Data{}.txt'.format(i)

liste_valeur = [] #liste des valeur lu dans le fichier

f = open(nom_fichier, 'r', encoding="latin-1")
temps = 0.8 #Temps d'execution du programme d'acquisition
nb_point = 0 #nombre de point valide dans le fichier

all_line = f.readlines()
for line in all_line:
    #Essaye de lire les donnée comme des float, ignore en cas de problème
    try:
        if float(line) >= 0:
            liste_valeur.append(float(line))
            nb_point+=1
    except:
        pass


x = np.linspace(0, temps, nb_point) #Crée l'axe du temp
barre2 = 300
barre = np.mean(liste_valeur)
barre = [barre, barre]
barre2 = [barre2, barre2]
d_barre = [0, temps]

#affiche
plt.plot()
plt.step(x, liste_valeur, label = "tension")
plt.plot(d_barre, barre, "red", label = "Moyenne")
#plt.plot(d_barre, barre2, "orange")
plt.title("Tension au cours du temps")
plt.xlabel("temps en secondes")
plt.ylabel("Sortie arduino")
plt.legend()
plt.show()

"""
plt.step(x, liste_valeur, where='post', label="Valeur entière")
plt.title("Tension au cours du temps", fontsize=14)
plt.xlabel("Temps (s)", fontsize=12)
plt.ylabel("Valeur entière (int)", fontsize=12)

plt.grid(True)

plt.tight_layout()
plt.show()
"""
