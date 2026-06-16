#include "engine.h"

bool verifier_modulo_R(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double x = 12.7;
    double q = 3.5;
    double y = modulo_R(x, q);
    double y_reel = 2.2;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur modulo_R(12.7, 3.5) != %lf valeur = %lf\n", y_reel, y);
    }

    x = -117;
    q = 17;
    y = modulo_R(x, q);
    y_reel = 2;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur modulo_R(-117, 17) != %lf valeur = %lf\n", y_reel, y);
    }

    x = -5.3;
    q = 4.3;
    y = modulo_R(x, q);
    y_reel = 3.3;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur modulo_R(-5.3, 4.3) != %lf valeur = %lf\n", y_reel, y);
    }

    return resultat;
}

bool verifier_abs_double(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double x = 5.6;
    double y =  abs_double(x);
    double y_reel = 5.6;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur abs_double(5.6) != %lf valeur = %lf\n", y_reel, y);
    }

    x = -5.6;
    y =  abs_double(x);
    y_reel = 5.6;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur abs_double(-5.6) != %lf valeur = %lf\n", y_reel, y);
    }
    return resultat;
}

bool verifier_affine_modulo(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double x = 12.7;
    double a = 2.1;
    double b = 8.6;
    double q = 3.5;
    double y = affine_modulo(a, b, q, x);
    double y_reel = 0.27;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur affine_modulo(2.1, 8.6, 3.5, 12.7) != %lf valeur = %lf\n", y_reel, y);
    }

    x = -12.7;
    a = 2.1;
    b = 8.6;
    q = 3.5;
    y = affine_modulo(a, b, q, x);
    y_reel = 2.93;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur affine_modulo(2.1, 8.6, 3.5, -12.7) != %lf valeur = %lf\n", y_reel, y);
    }

    return resultat;
}

bool verifier_forward_AM(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double * X = (double *)malloc(3*sizeof(double));
    X[0] = 5;
    X[1] = 2.6;
    X[2] = -13.6;
    double a = 2.1;
    double b = 8.6;
    double q = 3.5;
    int n = 3;
    double * y = forward_AM(a, b, q, X, n);
    double * Y_reel = (double *)malloc(3*sizeof(double));
    Y_reel[0] = 1.6;
    Y_reel[1] = 0.06;
    Y_reel[2] = 1.04;

    for (int i = 0; i<n; i++) {
        if ((y[i] <= Y_reel[i] - tolerance)||(y[i] >= Y_reel[i] + tolerance)) {
            resultat = false;
            printf("Erreur affine_modulo(2.1, 8.6, 3.5, %lf) != %lf valeur = %lf\n", X[i], Y_reel[i], y[i]);
        }
    }
    free(X);
    free(Y_reel);
    free(y);
    return resultat;
}

bool verifier_fun_cout_AM(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double * X1 = (double *)malloc(3*sizeof(double));
    X1[0] = 5;
    X1[1] = 2.6;
    X1[2] = -13.6;
    double * X2 = (double *)malloc(3*sizeof(double));
    X2[0] = -3;
    X2[1] = 7.9;
    X2[2] = -9.06;
    int n = 3;
    double y = fun_cout_AM(X1, X2, n);
    double y_reel = 37.5672;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur fun_cout_AM([5,2.6,-13.6], [-3,7.9,-9.06], 3) != %lf valeur = %lf\n", y_reel, y);
    }

    free(X1);
    free(X2);
    return resultat;
}

bool verifier_d_fun_cout_AM(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double * X1 = (double *)malloc(3*sizeof(double));
    X1[0] = 5;
    X1[1] = 2.6;
    X1[2] = -13.6;
    double * X2 = (double *)malloc(3*sizeof(double));
    X2[0] = -3;
    X2[1] = 7.9;
    X2[2] = -9.06;
    int n = 3;
    double y = d_fun_cout_AM(X1, X2, n);
    double y_reel = 1.2266666666;

    if ((y <= y_reel - tolerance)||(y >= y_reel + tolerance)) {
        resultat = false;
        printf("Erreur d_fun_cout_AM([5,2.6,-13.6], [-3,7.9,-9.06], 3) != %lf valeur = %lf\n", y_reel, y);
    }

    free(X1);
    free(X2);
    return resultat;
}

bool verifier_descent_gradient_AM(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double * X1 = (double *)malloc(3*sizeof(double));
    X1[0] = 5;
    X1[1] = 2.6;
    X1[2] = -13.6;
    double * X2 = (double *)malloc(3*sizeof(double));
    X2[0] = -3;
    X2[1] = 7.9;
    X2[2] = -9.06;
    int n = 3;
    double a = 4.6;
    double b = -5.2;
    double q = 7.2;
    double learning_rate = pow(10, -5);
    parametre_reseaux_AM * P = initialisation_parametre_reseaux_AM(a, b, q, X1, X2, learning_rate, n);
    retour_optimisation_AM * y = descente_gradient_AM(P);
    retour_optimisation_AM * Y_reel = initialisation_retour_optimisation_AM(4.60101229333333261451,-5.1998762667 , 73.04986666666688);

    if ((y->a <= Y_reel->a - tolerance)||(y->a >= Y_reel->a + tolerance)) {
        resultat = false;
        printf("Erreur descente_gradient_AM(4.6, -5.2, 7.2, [5,2.6,-13.6], [-3,7.9,-9.06], 10**-5, 3)->a != %lf valeur = %.20lf\n", Y_reel->a, y->a);
    }
    if ((y->b <= Y_reel->b - tolerance)||(y->b >= Y_reel->b + tolerance)) {
        resultat = false;
        printf("Erreur descente_gradient_AM(4.6, -5.2, 7.2, [5,2.6,-13.6], [-3,7.9,-9.06], 10**-5, 3)->b != %lf valeur = %lf\n", Y_reel->b, y->b);
    }
    if ((y->cout <= Y_reel->cout - tolerance)||(y->cout >= Y_reel->cout + tolerance)) {
        resultat = false;
        printf("Erreur descente_gradient_AM(4.6, -5.2, 7.2, [5,2.6,-13.6], [-3,7.9,-9.06], 10**-5, 3)->cout != %lf valeur = %lf\n", Y_reel->cout, y->cout);
    }

    free(X1);
    free(X2);
    free(y);
    free(Y_reel);
    free(P);
    return resultat;
}

bool verifier_apprentissage_AM(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    double * X1 = (double *)malloc(3*sizeof(double));
    X1[0] = 5;
    X1[1] = 2.6;
    X1[2] = -13.6;
    double * X2 = (double *)malloc(3*sizeof(double));
    X2[0] = -3;
    X2[1] = 7.9;
    X2[2] = -9.06;
    int n = 3;
    double a = 4.6;
    double b = -5.2;
    double q = 7.2;
    double learning_rate = pow(10, -5);
    parametre_reseaux_AM * P = initialisation_parametre_reseaux_AM(a, b, q, X1, X2, learning_rate, n);
    retour_optimisation_AM * y = apprentissage_AM(P, 100);
    retour_optimisation_AM * Y_reel = initialisation_retour_optimisation_AM(4.6943428505, -5.1878058630, 81.476294322750618);

    if ((y->a <= Y_reel->a - tolerance)||(y->a >= Y_reel->a + tolerance)) {
        resultat = false;
        printf("Erreur apprentissage_AM(4.6, -5.2, 7.2, [5,2.6,-13.6], [-3,7.9,-9.06], 10**-5, 3)->a != %lf valeur = %.10lf\n", Y_reel->a, y->a);
    }
    if ((y->b <= Y_reel->b - tolerance)||(y->b >= Y_reel->b + tolerance)) {
        resultat = false;
        printf("Erreur apprentissage_AM(4.6, -5.2, 7.2, [5,2.6,-13.6], [-3,7.9,-9.06], 10**-5, 3)->b != %lf valeur = %.10lf\n", Y_reel->b, y->b);
    }

    free(X1);
    free(X2);
    free(y);
    free(Y_reel);
    free(P);
    return resultat;
}

bool verifier_linespace(void) {
    bool resultat = true;
    double tolerance = pow(10,-10);

    intervalle * I = initialisation_intervalle(1, 2, 1, 2);
    double ** X = linespace(I, 3);
    double ** Y = (double **)malloc(3*3*sizeof(double *));
    for (int i = 0; i<3*3; i++) {
        Y[i] = (double *)malloc(2*sizeof(double)); 
    }
    Y[0][0] = 1;
    Y[0][1] = 1;
    Y[1][0] = 1;
    Y[1][1] = 1.5;
    Y[2][0] = 1;
    Y[2][1] = 2;
    Y[3][0] = 1.5;
    Y[3][1] = 1;
    Y[4][0] = 1.5;
    Y[4][1] = 1.5;
    Y[5][0] = 1.5;
    Y[5][1] = 2;
    Y[6][0] = 2;
    Y[6][1] = 1;
    Y[7][0] = 2;
    Y[7][1] = 1.5;
    Y[8][0] = 2;
    Y[8][1] = 2;

    for (int i = 0; i<3*3; i++) {
        for (int j = 0; j<2; j++) {
            if ((X[i][j] <= Y[i][j] - tolerance)||(X[i][j] >= Y[i][j] + tolerance)) {
                resultat = false;
                printf("Erreur linespace([1,2,1,2], 3)[%d][%d] != %lf valeur = %lf\n", i, j, X[i][j], Y[i][j]);
            }
        }
    }

    free(I);
    supprimer_tableau(X, 3*3);
    supprimer_tableau(Y, 3*3);
    return resultat;
}

void verifier(void) {
    bool resultat = true;
    resultat &= verifier_abs_double();
    resultat &= verifier_modulo_R();
    resultat &= verifier_affine_modulo();
    
    resultat &= verifier_forward_AM();
    resultat &= verifier_fun_cout_AM();
    resultat &= verifier_d_fun_cout_AM();
    /*
    les fonction d_a_AM, d_b_AM, d_fun_cout_a_AM, d_fun_cout_b_AM, initialisation_retour_optimisation_AM, initialisation_parametre_reseaux_AM sont correct car leur calcul est evident(elles sont la pour faciliter la lecture)
    */
    resultat &= verifier_descent_gradient_AM();
    resultat &= verifier_apprentissage_AM();

    resultat &= verifier_linespace();

    if (resultat == true) {
        printf("Tout va bien\n");
    }
}