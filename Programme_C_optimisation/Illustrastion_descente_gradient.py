import matplotlib.pyplot as plt
import numpy as np

def f(x,y):
    return (
        3 * (1 - x)**2 * np.exp(-x**2 - (y + 1)**2)
        - 10 * (x/5 - x**3 - y**5) * np.exp(-x**2 - y**2)
        - (1/3) * np.exp(-(x + 1)**2 - y**2)
    )

Chemin_x = [0.2, 0.7, 0.57, 0.6, 0.75, 0.5, 0.4, 0.3, 0.23]
Chemin_y = [1.3, 1, 0.5, -0.3, -0.75, -1.2, -1.4, -1.5, -1.6]

# Paramètres
N = 2000

centre = 2

a_min = -centre
a_max = centre

b_min = -centre
b_max = centre

x = np.linspace(a_min, a_max, N)
y = np.linspace(b_min, b_max, N)

# On passe "indexing='ij'" pour que X corresponde aux lignes (x) et Y aux colonnes (y)
X, Y = np.meshgrid(x, y, indexing="ij")

# 4. Reconstruction automatique de la matrice T
T = f(X, Y)

# Figure
plt.figure()

# Lignes de niveau
contours = plt.contour(X, Y, T, levels=50)
plt.plot(Chemin_x, Chemin_y, color = "yellow")
plt.scatter(Chemin_x, Chemin_y, color = "red", label="chemin descente gardient")
plt.colorbar(contours)

# Labels
plt.xlabel("x")
plt.ylabel("y")



plt.legend()

plt.tight_layout()

plt.show()