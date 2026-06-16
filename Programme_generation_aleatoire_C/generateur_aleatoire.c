#include "generateur_aleatoire.h"
#include <stdio.h>

Generateur_aleatoire * init_generateur(int generateur_utiliser) {
    Generateur_aleatoire * result = (Generateur_aleatoire *)malloc(sizeof(Generateur_aleatoire));
    result->gcl_int = NULL;
    result->gcl_double = NULL;
    result->g_logistique = NULL;
    result->g_physique = NULL;
    result->generateur_utiliser = generateur_utiliser;
    return result;
}

void init_generateur_congruenciel_int(Generateur_aleatoire * g, int a, int b, int q, int seed) {
    Generateur_congruenciel_int * gcl = (Generateur_congruenciel_int *)malloc(sizeof(Generateur_congruenciel_int));
    gcl->a = a;
    gcl->b = b;
    gcl->q = q;
    gcl->x = seed;
    g->gcl_int = gcl;
}

void init_generateur_congruenciel_double(Generateur_aleatoire * g, double a, double b, double q, double seed) {
    Generateur_congruenciel_double * gcl = (Generateur_congruenciel_double *)malloc(sizeof(Generateur_congruenciel_double));
    gcl->a = a;
    gcl->b = b;
    gcl->q = q;
    gcl->x = seed;
    g->gcl_double = gcl;
}

void init_generateur_logistique(Generateur_aleatoire * g, double alpha, double seed, int pas) {
    Generateur_logistique * g_l = (Generateur_logistique *)malloc(sizeof(Generateur_logistique));
    g_l->alpha = alpha;
    g_l->x = seed;
    g_l->pas = pas;
    g->g_logistique = g_l;
}

void init_generateur_physique(Generateur_aleatoire * g, char * nom) {
    FILE * f = fopen(nom, "r");
    if (f == NULL) {
        printf("Erreur de lecture de fichier dans init_generateur_physique\n");
        return;
    }
    char tampom[1000];
    int i_max = 0;
    while (fgets(tampom, 1000, f) != NULL) {
        i_max ++;
    }
    fclose(f);
    double * t = (double *)malloc(i_max*sizeof(double));
    f = fopen(nom, "r");
    if (f == NULL) {
        printf("Erreur de lecture de fichier dans init_generateur_physique\n");
        return;
    }
    int i = 0;
    char * end;
    while (fgets(tampom, 1000, f) != NULL) {
        t[i] = strtod(tampom, &end);
        i++;
    }
    fclose(f);
    Generateur_physique * g_p = (Generateur_physique *)malloc(sizeof(Generateur_physique));
    g_p->i = 0;
    g_p->i_max = i_max-1;
    g_p->t = t;
    g->g_physique = g_p;
}

void init_generateur_LSFR(Generateur_aleatoire * g, int * bit_initial, int n_bit, int * polynome, int n_polynome) {
    Generateur_LSFR * g_lsfr = (Generateur_LSFR *)malloc(sizeof(Generateur_LSFR));
    g_lsfr->n_memoire = n_bit;
    g_lsfr->n_polynome = n_polynome;
    g_lsfr->memoire = bit_initial;
    g_lsfr->polynome = polynome;
    g->g_lsfr = g_lsfr;
}

double abs_double(double x) {
    if (x<0){
        return -x;
    }
    return x;
}

double modulo_R_double(double x, double q) {
    double y = 0;
    while (y<abs_double(x)) {
        y += q;
    }
    
    if (x>=0) {
        return abs_double(x) - y + q;
    }
    else {
        return abs_double(abs_double(x) - y);
    }
}

double g_affine_modulo_double(Generateur_aleatoire * g) {
    double result = modulo_R_double((g->gcl_double->a*g->gcl_double->x+g->gcl_double->b), g->gcl_double->q);
    g->gcl_double->x = result;
    return result;
}

double g_affine_modulo_int(Generateur_aleatoire * g) {
    int result = modulo_R_double((g->gcl_int->a*g->gcl_int->x+g->gcl_int->b), g->gcl_int->q);
    g->gcl_int->x = result;
    return (double)result/(double)g->gcl_int->q;
}

double g_logistique(Generateur_aleatoire * g) {
    double result;
    for (int i = 0; i<g->g_logistique->pas; i++) {
        result = g->g_logistique->alpha*g->g_logistique->x*(1 - g->g_logistique->x);
        g->g_logistique->x = result;
    }
    return (2.0 / M_PI) * asin(sqrt(result));
}

double g_physique(Generateur_aleatoire * g) {
    double result = g->g_physique->t[g->g_physique->i];
    if (g->g_physique->i >= g->g_physique->i_max) {
        g->g_physique->i = 0;
    }
    else {
        g->g_physique->i += 1;
    }
    return result;
}

double g_lsfr(Generateur_aleatoire * g) {
    int * valeur_bin = (int *)malloc(63*sizeof(int)); 
    int s = 0;
    for (int i = 0; i<63; i++) {
        s = 0;
        for (int j = 0; j<g->g_lsfr->n_polynome; j++) {
            s += g->g_lsfr->memoire[g->g_lsfr->polynome[j]];
        }
        s = s % 2;
        valeur_bin[i] = g->g_lsfr->memoire[g->g_lsfr->n_memoire-1];
        for (int j = g->g_lsfr->n_memoire; j > 0; j--) {
            g->g_lsfr->memoire[j] = g->g_lsfr->memoire[j-1];
        }
        g->g_lsfr->memoire[0] = s;
    }
    ulong v = 0;
    ulong m = 0;
    for (int i = 0; i<63; i++) {
        v = 2*v + valeur_bin[i];
        m = 2*m + 1;
    }
    return (double)v/(double)m;
}

double g_aleatoire(Generateur_aleatoire * g) {
    if (g->generateur_utiliser == 2) {
        return g_affine_modulo_double(g);;
    }
    if (g->generateur_utiliser == 1) {
        return g_affine_modulo_int(g);
    }
    if (g->generateur_utiliser == 3) {
        return g_logistique(g);
    }
    if (g->generateur_utiliser == 4) {
        return g_physique(g);
    }
    if (g->generateur_utiliser == 5) {
        return g_lsfr(g);
    }
    printf("Pas de generateur defini\n");
    exit(1);
}

void ecrire_tableau(char * nom, double * t, int n) {
    FILE * f = fopen(nom, "w");
    for (int i = 0; i<n; i++) {
            fprintf(f, "%lf\n", t[i]);
    }
    fclose(f);
}