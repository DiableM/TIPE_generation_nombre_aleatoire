#include "engine.h"
#include <stdio.h>
#include <time.h>

int main(void) {
    verifier();
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int taille = 30;
    double q = 9854547;
    double * X = (double *)malloc(taille*sizeof(double));
    double * Y_reel = (double *)malloc(taille*sizeof(double));
    double a = 3580131;
    double b = 2766521;
    for(int i = 0; i<taille; i++) {
        X[i] = i;
        Y_reel[i] = affine_modulo(a, b, q, i);
    }
    double cherche_autour_a = 3580131.111508;
    double cherche_autour_b = 2766519.522335;
    double carre = 100;
    intervalle * I = initialisation_intervalle(cherche_autour_a - carre, cherche_autour_a + carre, cherche_autour_b - carre, cherche_autour_b + carre);
    retour_optimisation_AM ** resultat;
    int n_linespace = 2000;
    double learning_rate = 0.000000005;
    int nb_generation = 10;
    int nb_coeur = 16;
    for (int i = 0; i<0; i++) {
        start = clock();
        resultat = calcul_multicoeur_AM(I, n_linespace, q, X, Y_reel, taille, learning_rate, nb_generation, nb_coeur);
        retour_optimisation_AM * min = find_min_AM(resultat, n_linespace*n_linespace);
        printf("a = %lf, b = %lf, cout = %lf\n", min->a, min->b, min->cout);
        I = reduction_intervalle_AM(resultat, n_linespace*n_linespace, I);
        printf("a_min = %lf, a_max = %lf, b_min = %lf, b_max = %lf\n", I->a_min, I->a_max, I->b_min, I->b_max);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Temps CPU : %.4f secondes\n", cpu_time_used);
    }
    //resultat = calcul_multicoeur_AM(I, n_linespace, q, X, Y_reel, taille, learning_rate, nb_generation, nb_coeur);

    /*
    double ratio = 0.25;
    retour_optimisation_AM * min = find_min_AM(resultat, n_linespace*n_linespace);
    retour_optimisation_AM * max = find_max_AM(resultat, n_linespace*n_linespace);
    double cout_opti = (max->cout - min->cout)*0.5 + min->cout;
    tableau_cout_inf_X_sauvegarde("donnee_all3.txt", max->cout, resultat, n_linespace*n_linespace);
    //tableau_cout_inf_X_sauvegarde("donnee1.txt", cout_opti, resultat, n_linespace*n_linespace);
    cout_opti = (max->cout - min->cout)*ratio + min->cout;
    printf("cout_opti = %lf\n", cout_opti);
    //tableau_cout_inf_X_sauvegarde("donnee2.txt", cout_opti, resultat, n_linespace*n_linespace);
    cout_opti = (max->cout - min->cout)*0.15 + min->cout;
    //tableau_cout_inf_X_sauvegarde("donnee3.txt", cout_opti, resultat, n_linespace*n_linespace);
    cout_opti = (max->cout - min->cout)*0.05 + min->cout;
    //tableau_cout_inf_X_sauvegarde("donnee4.txt", cout_opti, resultat, n_linespace*n_linespace);
    cout_opti = (max->cout - min->cout)*0.005 + min->cout;
    //tableau_cout_inf_X_sauvegarde("donnee5.txt", cout_opti, resultat, n_linespace*n_linespace);
    cout_opti = max->cout;
    //tableau_cout_inf_X_sauvegarde("donnee6.txt", cout_opti, resultat, n_linespace*n_linespace);
    */

    int test = 0;
    int nb_test = 10000;
    double * valeur_relle = (double *)malloc(nb_test*sizeof(double));
    double * valeur_trouver = (double *)malloc(nb_test*sizeof(double));
    double tolerance = 1000;
    double init_X = ((double)rand()/(double)RAND_MAX)*(q-1);
    for (int i = 0; i<nb_test; i++) {
        init_X = ((double)rand()/(double)RAND_MAX)*(q-1);
        valeur_relle[i] = affine_modulo(a, b, q, init_X);
        valeur_trouver[i] = affine_modulo(3580130.998952, 2766521.010579, q, init_X);
        if (i%(nb_test/100) == 0) {
            printf("i = %d valeur %lf trouver %lf ecart %lf\n", i, valeur_relle[i], valeur_trouver[i], abs_double(valeur_relle[i]-valeur_trouver[i]));
        }
        if (abs_double(valeur_relle[i]-valeur_trouver[i])<tolerance) {
            test += 1;
        }
    }
    printf("réussit %lf\n", (double)test/(double)nb_test);
    /*
    parametre_reseaux_AM * P = initialisation_parametre_reseaux_AM(3580031, 2766621, q, X, Y_reel, learning_rate, taille);
    retour_optimisation_AM * calcul;
    double cout = 4406279991699.031250;
    double last_cout = cout;
    int i = 0;
    while (cout>10) {
        calcul = descente_gradient_AM(P);
        P->a = calcul->a;
        P->b = calcul->b;
        cout = calcul->cout;
        if (cout + 1<last_cout) {
            ecrire_chemin_descente_gradient("chemin_descente_gradient.txt", P->a, P->b = calcul->b);
            last_cout = cout;
            printf("cout = %lf\n", cout);
        }
        free(calcul);
    }
    */
    return 0;
}