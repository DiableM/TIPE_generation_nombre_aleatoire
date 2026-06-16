#include "engine.h"

double abs_double(double x) {
    if (x <= 0) {
        return -x;
    }
    else {
        return x;
    }
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void afficher_tableau_linespace(double ** X, int n) {
    for (int i = 0; i<n*n; i++) {
        printf("X[%d] = [%lf, %lf]\n", i, X[i][0], X[i][1]);
    }
}

intervalle * initialisation_intervalle(double a_min, double a_max, double b_min, double b_max) {
    intervalle * I = (intervalle *)malloc(sizeof(intervalle));
    I->a_min = a_min;
    I->a_max = a_max;
    I->b_min = b_min;
    I->b_max = b_max;
    return I;
}

retour_optimisation_AM * initialisation_retour_optimisation_AM(double a_initial, double b_initial, double cout) {
    retour_optimisation_AM * retour = (retour_optimisation_AM *)malloc(sizeof(retour_optimisation_AM));
    retour->a = a_initial;
    retour->b = b_initial;
    retour->cout = cout;
    return retour;
}

parametre_reseaux_AM * initialisation_parametre_reseaux_AM(double a, double b, double q, double * X, double * Y_reel, double learning_rate, int n) {
    parametre_reseaux_AM * retour = (parametre_reseaux_AM *)malloc(sizeof(parametre_reseaux_AM));
    retour->a = a;
    retour->b = b;
    retour->q = q;
    retour->X = X;
    retour->Y_reel = Y_reel;
    retour->learning_rate = learning_rate;
    retour->n = n;
    return retour;
}

double ** linespace(intervalle * I, int n) {
    // n est le cote du carre
    double ** X = (double **)malloc(n*n*sizeof(double *));
    for (int i = 0; i<n*n; i++) {
        X[i] = (double *)malloc(2*sizeof(double));
    }
    double a = I->a_min;
    double b = I->b_min;
    double ecart_a = (I->a_max - I->a_min)/(n-1);
    double ecart_b = (I->b_max - I->b_min)/(n-1);
    for (int i = 0; i<n; i++) {
        double b = I->b_min;
        for (int j = 0; j<n; j++) {
            X[i*n+j][0] = a;
            X[i*n+j][1] = b;
            b += ecart_b;
        }
        a += ecart_a;
    }
    return X;
}

void supprimer_tableau(double ** X, int n) {
    for (int i = 0; i<n; i++) {
        free(X[i]);
    }
    free(X);
}

void supprimer_donnee_AM(retour_optimisation_AM ** X, int n) {
    for (int i = 0; i<n; i++) {
        free(X[i]);
    }
    free(X);
}

retour_optimisation_AM * find_min_AM(retour_optimisation_AM ** tableau, int n) {
    retour_optimisation_AM * resultat = tableau[0];
    for (int i = 0; i<n; i++) {
        if (tableau[i]->cout < resultat->cout) {
            resultat = tableau[i];
        }
    }
    return resultat;
}

retour_optimisation_AM * find_max_AM(retour_optimisation_AM ** tableau, int n) {
    retour_optimisation_AM * resultat = tableau[0];
    for (int i = 0; i<n; i++) {
        if (tableau[i]->cout > resultat->cout) {
            resultat = tableau[i];
        }
    }
    return resultat;
}