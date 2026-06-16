#include "engine.h"
#include <stdio.h>

void tableau_cout_inf_X_sauvegarde(char * nom, double X, retour_optimisation_AM ** donnee, int n) {
    FILE * f = fopen(nom, "a");
    for (int i = 0; i<n; i++) {
        if (donnee[i]->cout < X) {
            fprintf(f, "a = %lf; b = %lf; cout = %lf\n", donnee[i]->a, donnee[i]->b, donnee[i]->cout);
        }
    }
    fclose(f);
}

void ecrire_chemin_descente_gradient(char * nom, double a, double b) {
    FILE * f = fopen(nom, "a");
    fprintf(f, "a = %lf; b = %lf\n", a, b);
    fclose(f);
}

retour_optimisation_AM ** tableau_cout_inf_X_tableau(int *tableau_fin, double X, retour_optimisation_AM ** donnee, int n) {
    retour_optimisation_AM ** t = (retour_optimisation_AM **)malloc(n*sizeof(retour_optimisation_AM *));
    *tableau_fin = 0;
    for (int i = 0; i<n; i++) {
        if (donnee[i]->cout < X) {
            t[*tableau_fin] = donnee[i];
            *tableau_fin += 1;
        }
    }
    return t;
}