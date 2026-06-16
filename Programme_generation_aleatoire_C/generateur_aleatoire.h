#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#ifndef GENERATEUR_ALEATOIRE_H
#define GENERATEUR_ALEATOIRE_H

typedef struct _generateur_congruenciel_int{
    int a;
    int b;
    int q;
    int x;
} Generateur_congruenciel_int;

typedef struct _generateur_congruenciel_double{
    double a;
    double b;
    double q;
    double x;
} Generateur_congruenciel_double;

typedef struct _generateur_logistique {
    double alpha;
    double x;
    int pas;
} Generateur_logistique;

typedef struct _generateur_physique {
    double * t;
    int i;
    int i_max;
} Generateur_physique;

typedef struct _generateur_LSFR {
    int * memoire;
    int n_memoire;
    int * polynome;
    int n_polynome;
} Generateur_LSFR;

typedef struct _generateur_aleatoire{
    Generateur_congruenciel_int * gcl_int; //1
    Generateur_congruenciel_double * gcl_double; //2
    Generateur_logistique * g_logistique; //3
    Generateur_physique * g_physique; //4
    Generateur_LSFR * g_lsfr; //5
    int generateur_utiliser;
} Generateur_aleatoire;

Generateur_aleatoire * init_generateur(int generateur_utiliser);
void init_generateur_congruenciel_int(Generateur_aleatoire * g, int a, int b, int q, int seed);
void init_generateur_congruenciel_double(Generateur_aleatoire * g, double a, double b, double q, double seed);
void init_generateur_logistique(Generateur_aleatoire * g, double alpha, double seed, int pas);
void init_generateur_physique(Generateur_aleatoire * g, char * nom);
void init_generateur_LSFR(Generateur_aleatoire * g, int * bit_initial, int n_bit, int * polynome, int n_polynome);
double abs_double(double x);
double modulo_R_double(double x, double q);
double g_affine_modulo_double(Generateur_aleatoire * g);
double g_affine_modulo_int(Generateur_aleatoire * g);
double g_logistique(Generateur_aleatoire * g);
double g_physique(Generateur_aleatoire * g);
double g_lsfr(Generateur_aleatoire * g);
double g_aleatoire(Generateur_aleatoire * g);
void ecrire_tableau(char * nom, double * t, int n);

#endif