#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "generateur_aleatoire.h"

typedef struct _graphe
{
    int taille_grille;
    int **adj;
} graphe;

bool bernoulli(float p, Generateur_aleatoire * g)
{
    double x = g_aleatoire(g);
    if (x <= p)
        return true;
    return false;
}

graphe *creer_grille(int taille, float p, Generateur_aleatoire * g_aleatoire)
{
    int n = taille * taille;
    graphe *g = (graphe *)malloc(sizeof(graphe));
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        int *ligne = (int *)calloc(n, sizeof(int));
        mat[i] = ligne;
    }
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            if (j > 0 && bernoulli(p, g_aleatoire))
            {
                mat[i * taille + j][i * taille + (j - 1)] = 1;
                mat[i * taille + (j - 1)][i * taille + j] = 1;
            }
            if (j < taille - 1 && bernoulli(p, g_aleatoire))
            {
                mat[i * taille + j][i * taille + (j + 1)] = 1;
                mat[i * taille + (j + 1)][i * taille + j] = 1;
            }
            if (i > 0 && bernoulli(p, g_aleatoire))
            {
                mat[(i - 1) * taille + j][i * taille + j] = 1;
                mat[i * taille + j][(i - 1) * taille + j] = 1;
            }
            if (i < taille - 1 && bernoulli(p, g_aleatoire))
            {
                mat[(i + 1) * taille + j][i * taille + j] = 1;
                mat[i * taille + j][(i + 1) * taille + j] = 1;
            }
        }
    }
    g->taille_grille = taille;
    g->adj = mat;
    return g;
}

void liberer_graphe(graphe *g)
{
    int nb_sommets = (g->taille_grille) * (g->taille_grille);
    for (int i = 0; i < nb_sommets; i++)
    {
        free((g->adj)[i]);
    }
    free(g->adj);
    free(g);
}

bool dfs(graphe *g, bool *vu, int k)
{
    int n = g->taille_grille;
    if (k >= n * (n - 1))
    {
        return true;
    }
    if (!vu[k])
    {
        vu[k] = true;
        for (int i = 0; i < n * n; i++)
        {
            if ((g->adj)[k][i] == 1)
            {
                if (dfs(g, vu, i))
                    return true;
            }
        }
    }
    return false;
}

bool percolation(graphe *g)
{
    int n = g->taille_grille;
    bool *vu = (bool *)malloc(n * n * sizeof(bool));
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < (n * n); i++)
        {
            vu[i] = false;
        }
        if (dfs(g, vu, j))
        {
            free(vu);
            return true;
        }
    }
    free(vu);
    return false;
}

float probabilite_perc(float p, int taille, int rep, Generateur_aleatoire * g_aleatoire)
{ // calculer rep avec loi faible des grands nombres
    float compt = 0;
    for (int i = 0; i < rep; i++)
    {
        graphe *g = creer_grille(taille, p, g_aleatoire);
        if (percolation(g))
        {
            compt++;
        }
        liberer_graphe(g);
    }
    float p_moyenne = compt / ((float)rep);
    return p_moyenne;
}

float *proba_perc_fct_p(int taille, int rep, int nb_test, Generateur_aleatoire * g_aleatoire)
{
    float pas = 1.0 / ((float)nb_test);
    float p = 0;
    float *proba = (float *)malloc(nb_test * sizeof(float));
    for (int i = 0; i < nb_test; i++)
    {
        proba[i] = probabilite_perc(p, taille, rep, g_aleatoire);
        p += pas;
    }
    return proba;
}

float estimation_pc(int taille, int rep, int nb_test, float acceptance, Generateur_aleatoire * g_aleatoire)
{
    int ind = 0;
    float *proba = proba_perc_fct_p(taille, rep, nb_test, g_aleatoire);
    while ((proba[ind] - acceptance) <= 0 && ind < nb_test)
    {
        ind++;
    }
    free(proba);
    float res = ((float)ind) / ((float)nb_test);
    return res;
}

int main(void)
{
    int taille = 20;
    int rep = 200;
    int nb_test = 500;
    float acceptance = 0.5;
    Generateur_aleatoire * g_aleatoire = init_generateur(4);
    //1=affine_module_doule 2=affini_modulo_int 3=logistique 4=physique 
    init_generateur_congruenciel_int(g_aleatoire, 65539, 0, 1073741824, 78);
    init_generateur_logistique(g_aleatoire, 4, 0.8921, 1);
    init_generateur_physique(g_aleatoire, "Donnee/liste_nb_aleatoire_physique.txt");
    srand(time(0));
    float res = estimation_pc(taille, rep, nb_test, acceptance, g_aleatoire);
    printf("\nseed = %ld\n", time(0));
    printf("p_c = %f\n", res);
    return 0;
}