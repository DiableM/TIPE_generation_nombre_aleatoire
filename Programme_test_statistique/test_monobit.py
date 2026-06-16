import matplotlib.pyplot as plt
import numpy as np

def liste_01_nombre(liste, i, nb_valeur, pas):
    p_2 = 2**(nb_valeur-1)
    n = 0
    for j in range(i, i+nb_valeur*pas, pas):
        n += p_2*liste[j]
        p_2 = p_2/2
    return n

#emplacement = 'courbe_TIPE/V2/3_{}.txt'
emplacement = 'Data{}.txt'
nom_sortie = 'liste_nb_aleatoire_physique.txt'
nom_sortie_binaire_txt = 'liste_bin.txt'
nom_sortie_binaire_bin = 'liste_bin.bin'
nb_prise = 1
barre = 0
nb_01_interpretation = 32
pas = 1
T = []
A = []
liste_01 = []
liste_nb_aleatoire = []
liste_nb_aleatoire_uniforme = []
nb_elt = 0
sortie_binaire_txt = True
sortie_binaire_bin = True


for i in range(nb_prise):
    f = open(emplacement.format(i), 'r', encoding="latin-1")
    contenu = f.readlines()

    for line in contenu:
        try:
            A.append(float(line))
            nb_elt += 1
        except:
            pass
    f.close()

A = np.array(A)
barre = np.mean(A)

for i in range(len(A)):
    if A[i] > barre:
        liste_01.append(1)
    else:
        liste_01.append(0)

for i in range(len(liste_01)//(nb_01_interpretation*pas)):
    liste_nb_aleatoire.append(liste_01_nombre(liste_01, i*nb_01_interpretation*pas, nb_01_interpretation, pas))
    liste_nb_aleatoire_uniforme.append(liste_nb_aleatoire[i]/(2**nb_01_interpretation))

nb_1 = 0
nb_2 = 0
k = 5
nb_correlation = 0

for i in range(len(liste_01)-k):
    if liste_01[i] == 1:
        nb_1 += 1
    else:
        nb_2 += 1

print(barre)
print("nb 1 = {} nb 2 = {}".format(nb_1/len(liste_01), nb_2/len(liste_01)))

for k in range(20):
    nb_correlation = 0
    for i in range(len(liste_01)-k):
        if liste_01[i] == liste_01[i+k]:
            nb_correlation += 1
    print("nb correlation = {} pour k = {}".format(nb_correlation/len(liste_01), k))

with open(nom_sortie, 'w') as f:
    for i in range(len(liste_nb_aleatoire_uniforme)):
        f.write('{}\n'.format(liste_nb_aleatoire_uniforme[i]))

if sortie_binaire_txt:
    with open(nom_sortie_binaire_txt, 'w') as f:
        for i in range(0, len(liste_01), nb_01_interpretation):
            for j in range(nb_01_interpretation):
                try:
                    f.write('{}'.format(liste_01[i+j]))
                except:
                    pass
            f.write('\n')

if sortie_binaire_bin:
    with open(nom_sortie_binaire_bin, "wb") as f:
        for i in range(len(liste_nb_aleatoire)):
            f.write(int(liste_nb_aleatoire[i]).to_bytes(4, "little"))