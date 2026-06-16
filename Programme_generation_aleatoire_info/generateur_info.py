import random

nom_sortie = 'liste_nb_aleatoire_physique.txt'
def AM(a, b, q, x):
    return (a*x+b)%q

def logistique(alpha, x):
    return alpha*x*(1-x)

a = 65539
b = 0
q = 2**31
alpha = 4
x = 1
n = 1000000


with open(nom_sortie, 'w') as f:
    for i in range(n):
        u = random.random()
        #u = i/n
        #for j in range(10):
        #    u = logistique(alpha, u)
        #f.write('{}\n'.format(u))
        x = AM(a,b,q, x)
        f.write('{}\n'.format(x/q))
        #f.write('{}\n'.format(random.random()))
