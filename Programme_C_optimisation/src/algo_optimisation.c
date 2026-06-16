#include "engine.h"

/*
AM = affine_modulo
*/

double * forward_AM(double a, double b, double q, double * X, int n) {
    double * Y = (double *)malloc(n*sizeof(double));
    for (int i = 0; i<n; i++) {
        Y[i] = modulo_R(a*X[i]+b, q);
    }
    return Y;
}

double fun_cout_AM(double * Y_reel, double * Y_final, int n) {
    double somme = 0;
    for (int i = 0; i<n; i++) {
        somme += (Y_reel[i]-Y_final[i])*(Y_reel[i]-Y_final[i]);
    }
    return somme/(double)n;
}

double d_fun_cout_AM(double * Y_reel, double * Y_final, int n) {
    double somme = 0;
    for (int i = 0; i<n; i++) {
        somme += -2*(Y_reel[i]-Y_final[i]);
    }
    return somme/n;
}

double d_a_AM(double x) {
    return x;
}

double d_b_AM() {
    return 1;
}

double d_fun_cout_a_AM(double Y_reel, double Y_final, double x, int n) {
    return (2*(Y_reel-Y_final)/n)*d_a_AM(x);
}

double d_fun_cout_b_AM(double * Y_reel, double * Y_final, int n) {
    return d_fun_cout_AM(Y_reel, Y_final, n)*d_b_AM();
}

retour_optimisation_AM * descente_gradient_AM(parametre_reseaux_AM * P) {
    double * Y_final = forward_AM(P->a, P->b, P->q, P->X, P->n);
    double grad_a = 0;
    double grad_b = d_fun_cout_b_AM(Y_final, P->Y_reel, P->n);
    for (int i = 0; i<P->n; i++) {
        grad_a += d_fun_cout_a_AM(Y_final[i], P->Y_reel[i], P->X[i], P->n);
    }
    retour_optimisation_AM * resultat = initialisation_retour_optimisation_AM(P->a - grad_a * P->learning_rate, P->b - grad_b * P->learning_rate, fun_cout_AM(P->Y_reel, Y_final, P->n));
    free(Y_final);
    return resultat;
}

retour_optimisation_AM * apprentissage_AM(parametre_reseaux_AM * P, int nb_generation) {
    retour_optimisation_AM * calcul;
    double cout = -1;
    for (int i = 0; i<nb_generation; i++) {
        calcul = descente_gradient_AM(P);
        P->a = calcul->a;
        P->b = calcul->b;
        cout = calcul->cout;
        ecrire_chemin_descente_gradient("chemin_descente_gradient.txt", P->a, P->b = calcul->b);
        free(calcul);
    }
    retour_optimisation_AM * retour = initialisation_retour_optimisation_AM(P->a, P->b, cout);
    return retour;
}

intervalle * reduction_intervalle_AM(retour_optimisation_AM ** donnee, int n, intervalle * initial) {
    double ratio = 0.25;

    intervalle * final = (intervalle *)malloc(sizeof(intervalle));
    retour_optimisation_AM * min = find_min_AM(donnee, n);
    retour_optimisation_AM * max = find_max_AM(donnee, n);
    double cout_opti = min->cout*ratio + min->cout;
    double dx = (initial->a_max-initial->a_min)/2;
    double dy = (initial->b_max-initial->b_min)/2;
    int taille_tableau_inf_X;
    double d_max = distance(0, 0, dx, dy);
    retour_optimisation_AM ** tableau_inf_X = tableau_cout_inf_X_tableau(&taille_tableau_inf_X, cout_opti, donnee, n);
    double * nb_voisin = (double *)malloc(taille_tableau_inf_X*sizeof(double));
    for (int i = 0; i<taille_tableau_inf_X; i++) {
        nb_voisin[i] = 0;
    }

    //calculer le nb de voisin pour chaque point dans le nouvelle intervalle
    for (int i = 0; i<taille_tableau_inf_X; i++) {
        for (int j = 0; j<taille_tableau_inf_X; j++) {
            if (distance(tableau_inf_X[i]->a, tableau_inf_X[i]->b, tableau_inf_X[j]->a, tableau_inf_X[j]->b) < d_max) {
                nb_voisin[i] += 1;
            }
        }
    }
    //trouver le point qui a le plus de voisin dans le nouvelle intervalle
    int i_max = 0;
    for (int i = 0; i<taille_tableau_inf_X; i++) {
        if (nb_voisin[i] > nb_voisin[i_max]) {
            i_max = i;
        }
    }
    final->a_min = tableau_inf_X[i_max]->a - dx/2;
    if (final->a_min<initial->a_min) {
        final->a_min = initial->a_min;
    }
    final->a_max = tableau_inf_X[i_max]->a + dx/2;
    if (final->a_max>initial->a_max) {
        final->a_max = initial->a_max;
    }
    final->b_min = tableau_inf_X[i_max]->b - dy/2;
    if (final->b_min<initial->b_min) {
        final->b_min = initial->b_min;
    }
    final->b_max = tableau_inf_X[i_max]->b + dy/2;
    if (final->b_max>initial->b_max) {
        final->b_max = initial->b_max;
    }

    supprimer_donnee_AM(donnee, n);
    free(tableau_inf_X);
    free(nb_voisin);
    free(initial);
    return final;
}