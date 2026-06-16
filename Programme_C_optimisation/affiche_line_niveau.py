import matplotlib.pyplot as plt
import numpy as np

# Lecture des données
def lire_points(fichier):
    cout = []

    with open(fichier, 'r') as f:
        for line in f:
            t = line.split(";")
            t1 = t[2].split("=")
            cout.append(float(t1[1]))
    return cout

def lire_chemin(fichier):
    chemin_x = []
    chemin_y = []
    i = 0
    with open(fichier, "r") as f:
        for line in f:
            if i%1 == 0:
                t = line.split(";")
                t1 = t[0].split("=")
                chemin_x.append(float(t1[1]))
                t1 = t[1].split("=")
                chemin_y.append(float(t1[1]))
            i += 1
    return chemin_x, chemin_y

# Paramètres
N = 2000

a_min = 3580031-200
a_max = 3580031+200

b_min = 2766621-200
b_max = 2766621+200

# Point particulier
a = 3580131
b = 2766521

# Chargement
z = lire_points("donnee_all.txt")
z.append(0)

chemin_x, chemin_y = lire_chemin("chemin_descente_gradient.txt")

# Reconstruction matrice
T = np.array(z).reshape(N, N)

# Axes
x = np.linspace(a_min, a_max, N)
y = np.linspace(b_min, b_max, N)

X, Y = np.meshgrid(x, y)

# Figure
plt.figure()

# Lignes de niveau
contours = plt.contour(X, Y, T.T, levels=100, cmap="inferno")

# Point minimum
plt.scatter([a], [b], color="blue", s=100, label="minimum")

# Labels
plt.xlabel("a")
plt.ylabel("b")
plt.plot(chemin_x, chemin_y, color="red", label="chemin descente gardient")
#plt.xlim(3580031 - 200, 3580031 + 200)
#plt.ylim(2766621 - 200, 2766621 + 200)


# Barre de couleur
plt.colorbar(label="cout")

plt.legend()

plt.tight_layout()

plt.show()