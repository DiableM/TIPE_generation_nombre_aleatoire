#include "../Programme_generation_aleatoire_C/generateur_aleatoire.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct _fonction {
    double * Y;
    double * t;
    int n;
} Fonction;

typedef struct _point {
    double x;
    double y;
} Point;

typedef struct _parametre_multicoeur {
    double * nb_aleatoire;
    int n;
    double x_min;
    double x_max;
    int nb_interval;
    Fonction * retour;
} Parametre_multicoeur;

void supprimer_fonction(Fonction * f) {
    free(f->Y);
    free(f->t);
    free(f);
}

Fonction * addition_fonction(Fonction * f, Fonction *g) {
    double * y = (double *)malloc(f->n*sizeof(double));
    double * t = (double *)malloc(f->n*sizeof(double));
    Fonction * r = (Fonction *)malloc(sizeof(Fonction));
    for (int i = 0; i<f->n; i++) {
        y[i] = f->Y[i] + g->Y[i];
        t[i] = f->t[i];
    }
    r->Y = y;
    r->t = t;
    r->n = f->n;
    return r;
}

Fonction * soustraction_fonction(Fonction * f, Fonction *g) {
    double * y = (double *)malloc(f->n*sizeof(double));
    double * t = (double *)malloc(f->n*sizeof(double));
    Fonction * r = (Fonction *)malloc(sizeof(Fonction));
    for (int i = 0; i<f->n; i++) {
        y[i] = f->Y[i] - g->Y[i];
        t[i] = f->t[i];
    }
    r->Y = y;
    r->t = t;
    r->n = f->n;
    return r;
}

Fonction * init_fonction(double x_min, double x_max, int n) {
    double * y = (double *)malloc((n+1)*sizeof(double));
    double * t = (double *)malloc((n+1)*sizeof(double));
    double dt = (x_max-x_min)/(n);
    Fonction * r = (Fonction *)malloc(sizeof(Fonction));
    for (int i = 0; i<n+1; i++) {
        y[i] = 0;
        t[i] = i*dt;
    }
    r->Y = y;
    r->t = t;
    r->n = n+1;
    return r;
}

void afficher_tableau(double * X, int n) {
    for (int i = 0; i<n; i++) {
        printf("%lf\n", X[i]);
    }
}

double produit_scalaire(Fonction * f_X, Fonction * f_Y) {
    double aire = 0;
    double dt = f_X->t[1];
    for (int i = 0; i<f_X->n; i++) {
        aire += f_X->Y[i]*f_Y->Y[i]*dt;
    }
    return aire;
}

double distcance(Point P1, Point P2) {
    return (P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y);
}

Fonction * approche_densiter(double * nb_aleatoire, int n, double x_min, double x_max, int nb_interval) {
    double * p_interval = (double *)malloc((nb_interval+1) * sizeof(double));
    double * t = (double *)malloc((nb_interval+1)*sizeof(double));
    Fonction * f = (Fonction *)malloc(sizeof(Fonction));
    f->Y = p_interval;
    f->t = t;
    f->n = nb_interval+1;
    double dt = (x_max-x_min)/(double) nb_interval;
    int n_liste = (n/2);
    Point * liste_point = (Point *)malloc( n_liste* sizeof(Point));
    double nb_distance = (double)n_liste*((double)n_liste-1)/2;
    for (int i = 0; i<n_liste; i++) {
        liste_point[i].x = nb_aleatoire[2*i];
        liste_point[i].y = nb_aleatoire[2*i+1];
    }
    for (int i = 0; i<nb_interval+1; i++) {
        t[i] = i*dt;
        p_interval[i] = 0;
    }
    int k;
    for (int i = 0; i<n_liste; i++) {
        for (int j = i+1; j<n_liste; j++) {
            k = floor(distcance(liste_point[i], liste_point[j])/dt);
            p_interval[k] += 1/(nb_distance*dt);
        }
    }
    free(liste_point);
    return f;
}

Fonction * densiter_theorique(double x_min, double x_max, int nb_interval) {
    double * Y = (double *)malloc((nb_interval+1) * sizeof(double));
    double * t = (double *)malloc((nb_interval+1)*sizeof(double));
    double dt = (x_max-x_min)/(double)(nb_interval);
    Fonction * f = (Fonction *)malloc(sizeof(Fonction));
    for (int i = 0; i<nb_interval+1; i++) {
        t[i] = i*dt;
        if (t[i]<1) {
            Y[i] = M_PI + t[i] - 4*sqrt(t[i]);
        }
        else {
            Y[i] = -2 + 4*asin(1/(sqrt(t[i]))) + 4*sqrt(t[i]-1) - M_PI - t[i];

        }
    }
    f->Y = Y;
    f->t = t;
    f->n = nb_interval+1;
    return f;
}

Parametre_multicoeur * init_parametre_multicoeur(int n, double x_min, double x_max, int nb_interval, Generateur_aleatoire * g) {
    Parametre_multicoeur * p = (Parametre_multicoeur *)malloc(sizeof(Parametre_multicoeur));
    double * nb_aleatoire = (double *)malloc(n*sizeof(double));
    for (int i = 0; i<n; i++) {
        nb_aleatoire[i] = g_aleatoire(g);
    }
    p->nb_aleatoire = nb_aleatoire;
    p->n = n;
    p->x_min = x_min;
    p->x_max = x_max;
    p->nb_interval = nb_interval;
    p->retour = NULL;
    return p;
}

void supprimer_parametre_multicoeur(Parametre_multicoeur * p) {
    free(p->nb_aleatoire);
    supprimer_fonction(p->retour);
    free(p);
}

void * calcul_approche_densiter_multicoeur(void * p_data) {
    Parametre_multicoeur * parametre = (Parametre_multicoeur *)p_data;
    Fonction * densiter = approche_densiter(parametre->nb_aleatoire,parametre->n, parametre->x_min, parametre->x_max, parametre->nb_interval);
    parametre->retour = densiter;
    return NULL;
}

Fonction * approche_densiter_multicoeur(double x_min, double x_max, int len_liste_nb_aleatoire, int nb_interval, int nb_coeur, int nb_iteration, Generateur_aleatoire * g) {
    Parametre_multicoeur ** liste_parametre_multicoeur = (Parametre_multicoeur **)malloc(nb_coeur*sizeof(Parametre_multicoeur *));
    pthread_t * tableau_coeur = (pthread_t *)malloc(nb_coeur*sizeof(pthread_t));
    Fonction * resultat = init_fonction(x_min, x_max, nb_interval);
    Fonction * f_temp;
    for (int i = 0; i<nb_iteration; i++) {
        printf("Generation %d\n", i);
        //allocation memoire
        for (int j = 0; j<nb_coeur; j++) {
            liste_parametre_multicoeur[j] = init_parametre_multicoeur(len_liste_nb_aleatoire, x_min, x_max, nb_interval, g);
        }
        //allocation calcul
        for (int j = 0; j<nb_coeur; j++) {
            pthread_create(&tableau_coeur[j], NULL, calcul_approche_densiter_multicoeur, (void *)liste_parametre_multicoeur[j]);
        }

        //recuperation resultat
        for (int j = 0; j<nb_coeur; j++) {
            pthread_join(tableau_coeur[j], NULL);
        }

        for (int j = 0; j<nb_coeur; j++) {
            f_temp = addition_fonction(resultat, liste_parametre_multicoeur[j]->retour);
            supprimer_fonction(resultat);
            supprimer_parametre_multicoeur(liste_parametre_multicoeur[j]);
            resultat = f_temp;
        }
    }
    for (int i = 0; i<nb_interval+1; i++) {
        resultat->Y[i] = resultat->Y[i]/(double)(nb_iteration*nb_coeur);
    }
    return resultat;
}

double approche_densiter_multicoeur_esperance(double x_min, double x_max, int len_liste_nb_aleatoire, int nb_interval, int nb_coeur, int nb_iteration, Generateur_aleatoire * g) {
    Parametre_multicoeur ** liste_parametre_multicoeur = (Parametre_multicoeur **)malloc(nb_coeur*sizeof(Parametre_multicoeur *));
    pthread_t * tableau_coeur = (pthread_t *)malloc(nb_coeur*sizeof(pthread_t));
    Fonction * f_th = densiter_theorique(x_min, x_max, nb_interval);
    double esperance = 0;
    double esperance_du_carre = 0;
    double nb_calcul  =(double)(nb_iteration*nb_coeur);
    Fonction * temp;
    for (int i = 0; i<nb_iteration; i++) {
        printf("Generation %d\n", i);
        //allocation memoire
        for (int j = 0; j<nb_coeur; j++) {
            liste_parametre_multicoeur[j] = init_parametre_multicoeur(len_liste_nb_aleatoire, x_min, x_max, nb_interval, g);
        }
        //allocation calcul
        for (int j = 0; j<nb_coeur; j++) {
            pthread_create(&tableau_coeur[j], NULL, calcul_approche_densiter_multicoeur, (void *)liste_parametre_multicoeur[j]);
        }

        //recuperation resultat
        for (int j = 0; j<nb_coeur; j++) {
            pthread_join(tableau_coeur[j], NULL);
        }

        for (int j = 0; j<nb_coeur; j++) {
            temp = soustraction_fonction(liste_parametre_multicoeur[j]->retour, f_th);
            double valeur = produit_scalaire(temp, temp);
            esperance += valeur/nb_calcul;
            esperance_du_carre += valeur*valeur/nb_calcul;
            supprimer_fonction(temp);
            supprimer_parametre_multicoeur(liste_parametre_multicoeur[j]);
        }
    }
    printf("esperance final = %.30lf\n", esperance);
    printf("esperance du carre final = %.30lf\n", esperance_du_carre);
    return esperance;
}

int main(void) {
    //1=affine_module_int 2=affini_modulo_double 3=logistique 4=physique 
    Generateur_aleatoire * g = init_generateur(1);
    init_generateur_congruenciel_int(g, 65539, 0, 1073741824, 78);
    //init_generateur_congruenciel_int(g, 23, 19, 60006, 55);
    init_generateur_logistique(g, 4, 0.8921, 30);
    init_generateur_physique(g, "liste_nb_aleatoire_physique.txt");
    //x_min, x_max len_liste_nb_aleaoire nb_intervalle nb_coeur nb_rep generateur
    //Fonction * d = approche_densiter_multicoeur(0, 2, 10000, 10000, 4, 10, g);
    //ecrire_tableau("test.txt", d->Y, d->n);
    double esperance = approche_densiter_multicoeur_esperance(0, 2, 100000, 100000, 4, 10, g);
    return 0;
}