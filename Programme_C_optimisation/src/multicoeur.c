#include "engine.h"
#include <stdio.h>

parametre_reseaux_multicoeur_AM * initialisation_parametre_reseaux_multicoeur_AM(double a, double b, double q, double * X, double * Y_reel, double learning_rate, int n, int nb_generation) {
    parametre_reseaux_multicoeur_AM * retour = (parametre_reseaux_multicoeur_AM *)malloc(sizeof(parametre_reseaux_multicoeur_AM));
    retour->P = initialisation_parametre_reseaux_AM(a, b, q, X, Y_reel, learning_rate, n);
    retour->nb_generation = nb_generation;
    return retour;
}

void * apprentissage_multicoeur_AM(void *p_data) {
    parametre_reseaux_multicoeur_AM * P_multicoeur = (parametre_reseaux_multicoeur_AM *)p_data;
    parametre_reseaux_AM * P = P_multicoeur->P;
    int nb_generation = P_multicoeur->nb_generation;

    retour_optimisation_AM * calcul;
    double cout = -1;
    for (int i = 0; i<nb_generation; i++) {
        calcul = descente_gradient_AM(P);
        P->a = calcul->a;
        P->b = calcul->b;
        cout = calcul->cout;
        free(calcul);
    }
    retour_optimisation_AM * retour = initialisation_retour_optimisation_AM(P->a, P->b, cout);
    return (void *)retour;
}

retour_optimisation_AM ** calcul_multicoeur_AM(intervalle * I, int n_linespace, double q, double * X, double * Y_reel, int taille, double learning_rate, int nb_generation, int nb_coeur) {
    retour_optimisation_AM ** resultat = (retour_optimisation_AM **)malloc(n_linespace*n_linespace*sizeof(retour_optimisation_AM *));
    double ** X_a_b = linespace(I, n_linespace);
    pthread_t * tableau_coeur = (pthread_t *)malloc(nb_coeur*sizeof(pthread_t));
    parametre_reseaux_multicoeur_AM ** tableau_parametre_reseaux_multicoeur_AM = (parametre_reseaux_multicoeur_AM **)malloc(nb_coeur*sizeof(parametre_reseaux_multicoeur_AM *));

    double progression = 0.01;
    for (int i = 0; i<(n_linespace*n_linespace)/nb_coeur; i++) {
        if ((double)i/((double)n_linespace*n_linespace/nb_coeur) >= progression) {
            progression += 0.01;
            printf("calcul effectuer a %lf%%\n", (double)i/((double)n_linespace*n_linespace/nb_coeur)*100);
        }
        //allocation mémoire
        for (int j = 0; j<nb_coeur; j++) {
            tableau_parametre_reseaux_multicoeur_AM[j] = initialisation_parametre_reseaux_multicoeur_AM(X_a_b[i*nb_coeur+j][0], X_a_b[i*nb_coeur+j][1], q, X, Y_reel, learning_rate, taille, nb_generation);
        }

        //allocation calcul
        for (int j = 0; j<nb_coeur; j++) {
            pthread_create(&tableau_coeur[j], NULL, apprentissage_multicoeur_AM, (void *)tableau_parametre_reseaux_multicoeur_AM[j]);
        }

        //recuperation resultat
        for (int j = 0; j<nb_coeur; j++) {
            pthread_join(tableau_coeur[j], (void**)&resultat[i*nb_coeur+j]);
        }

        //supprimer memoire
        for (int j = 0; j<nb_coeur; j++) {
            free(tableau_parametre_reseaux_multicoeur_AM[j]->P);
            free(tableau_parametre_reseaux_multicoeur_AM[j]);
        }
    }

    //gestion reste des calcul quand pas divisible par nb_coeur

    int i = (n_linespace*n_linespace)/nb_coeur;
    //allocation mémoire
    for (int j = 0; j<(n_linespace*n_linespace)%nb_coeur; j++) {
        tableau_parametre_reseaux_multicoeur_AM[j] = initialisation_parametre_reseaux_multicoeur_AM(X_a_b[i*nb_coeur+j][0], X_a_b[i*nb_coeur+j][1], q, X, Y_reel, learning_rate, taille, nb_generation);
    }

    //allocation calcul
    for (int j = 0; j<(n_linespace*n_linespace)%nb_coeur; j++) {
        pthread_create(&tableau_coeur[j], NULL, apprentissage_multicoeur_AM, (void *)tableau_parametre_reseaux_multicoeur_AM[j]);
    }

    //recuperation resultat
    for (int j = 0; j<(n_linespace*n_linespace)%nb_coeur; j++) {
        pthread_join(tableau_coeur[j], (void**)&resultat[i*nb_coeur+j]);
    }

    //supprimer memoire
    for (int j = 0; j<(n_linespace*n_linespace)%nb_coeur; j++) {
        free(tableau_parametre_reseaux_multicoeur_AM[j]->P);
        free(tableau_parametre_reseaux_multicoeur_AM[j]);
    }

    return resultat;
}