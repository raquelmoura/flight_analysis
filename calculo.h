#ifndef ___CALCULO_H___
#define ___CALCULO_H___

#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h> // windows
// #include "SDL/SDL.h" // linux

#define PI 3.14159265358979323846
#define GRAFX 0
#define GRAFY 1
#define MAXI 0
#define MINI 1
#define EX 2

typedef enum {TF, DT, S, B, M, G, RHO, CD0, E, ALPHA, Vi, GAMMAi, Xi, Hi} INT;
typedef enum {TEMPO, VEL, GAMMA, DIST, ALT} INT1;

void create_file (double parametros[]);

int max_min(double varia[], double maxmin[][3], char nome[]);
int grafico(double maxmin[][3], double varia[], char nome[]);
int pedex();
int pedey();

double cd (double parametros[], double epslon1, double cl1);
double cl (double parametros[]);
double epslon (double parametros[], double ar1);
double ar (double parametros[]);

#endif
