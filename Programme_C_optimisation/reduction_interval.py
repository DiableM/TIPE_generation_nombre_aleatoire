import matplotlib.pyplot as plt
import matplotlib.patches as patches

def lire_donnee(fichier):
    liste_carre = []

    with open(fichier, 'r') as f:
        for line in f:
            t1 = line.replace(",", "=").split("=")
            if t1[0] == "a_min ":
                t = []
                t.append((float(t1[1]), float(t1[5])))
                t.append((float(t1[1]), float(t1[7])))
                t.append((float(t1[3]), float(t1[7])))
                t.append((float(t1[3]), float(t1[5])))
                liste_carre.append(t)
    return liste_carre

q = 9854547

# Liste de vos points sous forme de couples (x, y)
points = lire_donnee("Point_reduction_intervalle.txt")

fig, ax = plt.subplots()

for i in range(len(points)):
    # Création du polygone (pas besoin de répéter le premier point ici, matplotlib le fait seul)c
    carre = patches.Polygon(points[i], closed=True, facecolor='skyblue', edgecolor='blue', linewidth=2)
    ax.add_patch(carre)

# Ajuster les limites des axes automatiquement pour voir le carré
ax.autoscale()
ax.set_aspect('equal')
ax.set
plt.title("Différents intervalles")
plt.xlim(0, q)
plt.ylim(0, q)
plt.xlabel("a")
plt.ylabel("b")


plt.show()