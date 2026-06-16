import matplotlib.pyplot as plt
import numpy as np
import re

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

def charger_donnees(nom_fichier):
    """Extrait les colonnes a, b et cout du fichier texte."""
    a_list, b_list, z_list = [], [], []
    
    try:
        with open(nom_fichier, 'r') as f:
            for line in f:
                # Trouve tous les nombres (entiers ou décimaux)
                nombres = re.findall(r"[-+]?\d*\.\d+|\d+", line)
                if len(nombres) >= 3:
                    a_list.append(float(nombres[0]))
                    b_list.append(float(nombres[1]))
                    z_list.append(float(nombres[2]))
    except FileNotFoundError:
        print(f"Erreur : Le fichier {nom_fichier} est introuvable.")
        return None
        
    return np.array(a_list), np.array(b_list), np.array(z_list)

# --- CONFIGURATION ---
FICHIER = "donnee_all2.txt"
chemin_x, chemin_y = lire_chemin("chemin_descente_gradient.txt")

N = 2000  # Taille de la grille (20x20 = 400 points)
a = 3580131
b = 2766521


# 1. Chargement des données
a_raw, b_raw, z_raw = charger_donnees(FICHIER)

if a_raw is not None:
    # 2. Gestion de l'erreur des 399 points
    # On crée un tableau de 400 éléments pour éviter le crash du reshape
    z_final = np.zeros(N * N)
    nb_points_reels = len(z_raw)
    
    # On remplit avec les données existantes
    z_final[:nb_points_reels] = z_raw[:N*N]
    
    # Si il manque un point, on lui donne la valeur du précédent pour ne pas casser le log
    if nb_points_reels < N * N:
        print(f"Attention : {nb_points_reels} points trouvés au lieu de {N*N}. Correction appliquée.")
        z_final[nb_points_reels:] = z_raw[-1]

    # 3. Reconstruction de la matrice de coût (Z)
    # On transpose ( .T ) selon l'ordre de tes boucles en C
    Z = z_final.reshape(N, N).T

    # 4. Création des axes X et Y (graduations)
    # On utilise les bornes réelles de tes données
    x_axis = np.linspace(a_raw.min(), a_raw.max(), N)
    y_axis = np.linspace(b_raw.min(), b_raw.max(), N)

    # 5. Affichage de la surface 2D
    plt.figure()
    
    # Utilisation de LogNorm car tes données varient de 10^5 à 10^12
    surface = plt.pcolormesh(x_axis, y_axis, Z, 
                             shading='gouraud', # 'gouraud' lisse les couleurs, 'auto' garde les carrés
                             cmap='magma', 
                             norm=plt.matplotlib.colors.LogNorm())

    # Ajout des éléments de lecture
    cbar = plt.colorbar(surface)
    cbar.set_label('Coût (Échelle logarithmique)', rotation=270, labelpad=15)
    
    plt.xlabel("Paramètre a")
    plt.ylabel("Paramètre b")
    plt.title("Chemin dans la descente du gradient")
    plt.plot(chemin_x, chemin_y, color="red", label="chemin descente gardient")
    plt.scatter([a], [b], color="blue", s=100, label="minimum")

    # Optionnel : On peut ajouter les points de calcul par dessus pour vérifier la grille
    # plt.scatter(a_raw, b_raw, c='white', s=2, alpha=0.2)

    plt.legend()
    plt.tight_layout()
    plt.savefig("surface_chemin.png")
    plt.show()