import matplotlib.pyplot as plt
import re

# Fonction pour lire les données depuis un fichier
def lire_points(fichier):
    a_vals, b_vals = [], []
    with open(fichier, 'r') as f:
        for ligne in f:
            match = re.search(r'a = ([\d\.\-e]+); b = ([\d\.\-e]+); cout = ([\d\.\-e]+)', ligne)
            if match:
                a = float(match.group(1))
                b = float(match.group(2))
                a_vals.append(a)
                b_vals.append(b)
    return a_vals, b_vals

a = 3580131
b = 2766521
q = 9854547

# Liste des fichiers et des couleurs associées
nom_fichier = 'Donnee/Donnee_programme_C/Valeur_fonction_cout_a_max_b_max/donnee{}.txt'
nb_fichier = 4
fichiers = []
for i in range(nb_fichier):
    fichiers.append(nom_fichier.format(i+2))
valeur = ['0.25','0.15', '0.05', '0.005', 'all']
couleurs = ['blue','green', 'yellow', 'red', 'black']

# Tracer les points
plt.figure(figsize=(8, 6))
for fichier, couleur, valeur in zip(fichiers, couleurs, valeur):
    a_vals, b_vals = lire_points(fichier)
    plt.scatter(a_vals, b_vals, color=couleur, label=valeur)

plt.xlabel('a')
plt.ylabel('b')
plt.title('Points en fonction de a et b')
plt.legend()
plt.grid(True)
plt.scatter(a,b, s=200, c='purple')
plt.tight_layout()
#plt.xlim(3*10**6, 4*10**6)
#plt.ylim(10**4, 10**7)
plt.savefig("fig2.png", dpi=150, bbox_inches="tight")
plt.show()
