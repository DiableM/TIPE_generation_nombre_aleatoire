import numpy as np
import matplotlib.pyplot as plt

def AM(a, b, q, x):
    return (a*x+b)%q

a = 65539
b = 0
q = 2**31
seed = 1

u_n = [seed]
x = seed
for i in range(0, 10000): #17 sans_rep
    x = (a*x)%q
    u_n.append(x)

u_n_reel = []
for elt in u_n:
    u_n_reel.append(elt/q)

barre = []
nb_par_barre = []
nb_barre = 100
for i in range(0, nb_barre+1):
    barre.append(i/nb_barre)
    nb_par_barre.append(0)

for elt in u_n_reel:
    i = 0
    while elt-10**-50 >= barre[i]:
        i += 1
    nb_par_barre[i-1] += 1

#plt.plot(barre, nb_par_barre)
#plt.show()

print(u_n)

X1 = []
Y1 = []
Z1 = []
for i in range(0, len(u_n_reel)//3):
    X1.append(u_n_reel[3*i])
    Y1.append(u_n_reel[3*i+1])
    Z1.append(u_n_reel[3*i+2])
    print("x=", u_n[3*i], "y=", u_n[3*i+1], "z=", u_n[3*i+2])


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(X1, Y1, Z1, c ='blue', s = 0.5)
plt.xlabel("X")
plt.ylabel("Y")

plt.show()
