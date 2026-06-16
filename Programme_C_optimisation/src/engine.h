#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

typedef struct retour_optimisation_AM_ {
    double a;
    double b;
    double cout;
} retour_optimisation_AM;

typedef struct parametre_reseaux_AM_ {
    double a;
    double b;
    double q;
    double * X;
    double * Y_reel;
    double learning_rate;
    int n;
} parametre_reseaux_AM;

typedef struct parametre_reseaux_multicoeur_AM_ {
    parametre_reseaux_AM * P;
    int nb_generation;
} parametre_reseaux_multicoeur_AM;

typedef struct intervalle_ {
    double a_min;
    double a_max;
    double b_min;
    double b_max;
} intervalle;

/*
#######################################################################################
                        fonction_generation_aleatoire.c
#######################################################################################
*/
double modulo_R(double x, double q);
double affine_modulo(double a, double b, double q, double x);

/*
#######################################################################################
                        fonction_generique.c
#######################################################################################
*/
double abs_double(double x);
double distance(double x1, double y1, double x2, double y2);
void afficher_tableau_linespace(double ** X, int n);
intervalle * initialisation_intervalle(double a_min, double a_max, double b_min, double b_max);
retour_optimisation_AM * initialisation_retour_optimisation_AM(double a_initial, double b_initial, double cout);
parametre_reseaux_AM * initialisation_parametre_reseaux_AM(double a, double b, double q, double * X, double * Y_reel, double learning_rate, int n);
double ** linespace(intervalle * I, int n);
void supprimer_tableau(double ** X, int n);
void supprimer_donnee_AM(retour_optimisation_AM ** X, int n);
retour_optimisation_AM * find_min_AM(retour_optimisation_AM ** tableau, int n);
retour_optimisation_AM * find_max_AM(retour_optimisation_AM ** tableau, int n);


/*
#######################################################################################
                        algo_optimisation.c
#######################################################################################
*/
double * forward_AM(double a, double b, double q, double * X, int n);
double fun_cout_AM(double * Y_reel, double * Y_final, int n);
double d_fun_cout_AM(double * Y_reel, double * Y_final, int n);
double d_a_AM(double x);
double d_b_AM();
double d_fun_cout_a_AM(double Y_reel, double Y_final, double x, int n);
double d_fun_cout_b_AM(double * Y_reel, double * Y_final, int n);
retour_optimisation_AM * descente_gradient_AM(parametre_reseaux_AM * P);
retour_optimisation_AM * apprentissage_AM(parametre_reseaux_AM * P, int nb_generation);
intervalle * reduction_intervalle_AM(retour_optimisation_AM ** donnee, int n, intervalle * initial);

/*
#######################################################################################
                        multicoeur.c
#######################################################################################
*/
parametre_reseaux_multicoeur_AM * initialisation_parametre_reseaux_multicoeur_AM(double a, double b, double q, double * X, double * Y_reel, double learning_rate, int n, int nb_generation);
void * apprentissage_multicoeur_AM(void *p_data);
retour_optimisation_AM ** calcul_multicoeur_AM(intervalle * I, int n_linespace, double q, double * X, double * Y_reel, int taille, double learning_rate, int nb_generation, int nb_coeur);

/*
#######################################################################################
                        gestion_donnee.c
#######################################################################################
*/
void tableau_cout_inf_X_sauvegarde(char * nom, double X, retour_optimisation_AM ** donnee, int n);
void ecrire_chemin_descente_gradient(char * nom, double a, double b);
retour_optimisation_AM ** tableau_cout_inf_X_tableau(int *tableau_fin, double X, retour_optimisation_AM ** donnee, int n);

/*
#######################################################################################
                        fichier_test.c
#######################################################################################
*/
void verifier(void);

#endif // ENGINE_H_