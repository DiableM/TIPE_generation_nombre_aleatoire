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
emplacement1 = '/media/msoucaze/Partage/Archive_cours/TIPE/acquisition_final1/Data{}.txt'
emplacement2 = '/media/msoucaze/Partage/Archive_cours/TIPE/acquisition_final2/Data{}.txt'
nom_sortie = 'liste_nb_aleatoire_physique.txt'
nom_sortie_binaire_txt = 'liste_bin.txt'
nom_sortie_binaire_bin = 'liste_bin.bin'
nb_prise1 = 22
nb_prise2 = 10
barre1 = 0
barre2 = 0
nb_01_interpretation = 32
pas = 1
T = []
A1 = []
A2 = []
liste_01 = []
liste_nb_aleatoire = []
liste_nb_aleatoire_uniforme = []
nb_elt = 0
sortie_txt = True
sortie_binaire_txt = True
sortie_binaire_bin = True


for i in range(nb_prise1):
    f = open(emplacement1.format(i), 'r', encoding="latin-1")
    contenu = f.readlines()

    for line in contenu:
        try:
            A1.append(float(line))
            nb_elt += 1
        except:
            pass
    f.close()

for i in range(nb_prise2):
    f = open(emplacement2.format(i), 'r', encoding="latin-1")
    contenu = f.readlines()

    for line in contenu:
        try:
            A2.append(float(line))
            nb_elt += 1
        except:
            pass
    f.close()

A1 = np.array(A1)
A2 = np.array(A2)
barre1 = np.mean(A1)
barre2 = np.mean(A2)
nb_1 = 0
nb_0 = 0


for i in range(len(A1)):
    if A1[i] > barre1:
        liste_01.append(1)
        nb_1 += 1
    else:
        liste_01.append(0)
        nb_0 += 1

for i in range(len(A2)):
    if A2[i] > barre2:
        liste_01.append(1)
        nb_1 += 1
    else:
        liste_01.append(0)
        nb_0 += 1
print("nb_1 = {}, nb_0 = {}".format(nb_1/(nb_1+nb_0), nb_0/(nb_1+nb_0)))


for i in range(len(liste_01)//(nb_01_interpretation*pas)):
    liste_nb_aleatoire.append(liste_01_nombre(liste_01, i*nb_01_interpretation*pas, nb_01_interpretation, pas))
    liste_nb_aleatoire_uniforme.append(liste_nb_aleatoire[i]/(2**nb_01_interpretation))

print("nb valeur", nb_elt)

if sortie_txt:
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