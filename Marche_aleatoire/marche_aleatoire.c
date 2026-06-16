#include "../Programme_generation_aleatoire_C/generateur_aleatoire.h"
#include <raylib.h>
#include <stdio.h>
#include <time.h>

typedef struct _particule {
    double x;
    double y;
} Particule;

typedef struct _univers {
    Particule ** tab;
    int nb;
} Univers;

void object_render(Univers * u) {
    double radius = 1;
    for (int i = 0; i<u->nb; i++) {
        DrawCircle(u->tab[i]->x, u->tab[i]->y, radius, RAYWHITE);
    }
}

void render(Camera2D camera, Univers * u) {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);

    object_render(u);

    EndMode2D();
    EndDrawing();
}

Univers * init_univers(double x, double y, int nb) {
    Particule ** t = (Particule **)malloc(nb*sizeof(Particule *));
    for (int i = 0; i<nb; i++) {
        t[i] = (Particule *)malloc(sizeof(Particule));
        t[i]->x = x;
        t[i]->y = y;
    }
    Univers * u = (Univers *)malloc(sizeof(Univers));
    u->nb = nb;
    u->tab = t;
    return u;
}

void mouvement_aleatoire(Univers * u, Generateur_aleatoire * g) {
    double alpha;
    double v = 1;
    for (int i = 0; i<u->nb; i++) {
        alpha = g_aleatoire(g) * 2*M_PI;
        u->tab[i]->x += v*cos(alpha);
        u->tab[i]->y += v*sin(alpha);
    }   
}

void afficher_variable(int variable, double x, double y) {
    char * str = malloc(20*sizeof(char));
    sprintf(str,"%d", variable);
    DrawText(str, x, y, 50, RAYWHITE);
}


int main(void){
    Camera2D camera = {0};
    int width = 600;
    int heigth = width;
    InitWindow(width, heigth, "Marche_aleatoire");
    camera.target = (Vector2){0, 0}; // le centre du cercle
    camera.offset = (Vector2){width/2.0f, heigth/2.0f}; // centre de l'écran
    camera.zoom = 2; // zoom normal
    camera.rotation = 0;
    struct timespec ts;
    ts.tv_sec = 0;            // secondes
    ts.tv_nsec = 10 * 1000000; // nanosecondes -> 500 ms

    Univers * u = init_univers(0, 0, 10000);
    Generateur_aleatoire * g = init_generateur(4);
    init_generateur_congruenciel_int(g, 23, 19, 60006, 55);
    //init_generateur_congruenciel_int(g, 374218, 28460991, 68822490, 55);

    init_generateur_logistique(g, 4, 0.10932, 10);
    //init_generateur_physique(g, "Donnee/liste_nb_aleatoire_physique.txt");
    init_generateur_physique(g, "liste_nb_aleatoire_physique.txt");

    int * memoire_lsfr = (int *)malloc(16*sizeof(int));
    int * polynome_lsfr = (int *)malloc(5*sizeof(int));
    memoire_lsfr[0] = 0;
    memoire_lsfr[1] = 0;
    memoire_lsfr[2] = 0;
    memoire_lsfr[3] = 1;
    memoire_lsfr[4] = 0;
    memoire_lsfr[5] = 0;
    memoire_lsfr[6] = 0;
    memoire_lsfr[7] = 1;
    memoire_lsfr[8] = 1;
    memoire_lsfr[9] = 1;
    memoire_lsfr[10] = 0;
    memoire_lsfr[11] = 0;
    memoire_lsfr[12] = 1;
    memoire_lsfr[13] = 0;
    memoire_lsfr[14] = 0;
    memoire_lsfr[15] = 1;

    polynome_lsfr[0] = 0;
    polynome_lsfr[1] = 10;
    polynome_lsfr[2] = 12;
    polynome_lsfr[3] = 13;
    polynome_lsfr[4] = 15;
    init_generateur_LSFR(g, memoire_lsfr, 16, polynome_lsfr, 5);
    //1=affine_module_int 2=affini_modulo_double 3=logistique 4=physique 5=lsfr

    int frame = 0;
    while (!WindowShouldClose()) {
        render(camera, u);
        afficher_variable(frame, 100, 150);
        mouvement_aleatoire(u, g);
        if (frame == 41) {
            TakeScreenshot("marche_aleatoire_congruentiel1.png");
        }
        if (frame == 101) {
            TakeScreenshot("marche_aleatoire_congruentiel2.png");
        }
        if (frame == 401) {
            TakeScreenshot("marche_aleatoire_congruentiel3.png");
        }
        if (frame == 1001) {
            TakeScreenshot("marche_aleatoire_congruentiel4.png");
        }
        nanosleep(&ts, NULL);
        frame++;
    }
    return 0;
}