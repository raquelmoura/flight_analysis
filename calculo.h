#ifndef ___CALCULO_H___
#define ___CALCULO_H___

#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h> // windows
// #include "SDL/SDL.h" // linux

#define PI 3.14159265358979323846


typedef enum {TF, DT, S, B, M, G, RHO, CD0, E, ALPHA, Vi, GAMMAi, Xi, Hi} INT;


void create_file (double parametros[]);



double cd (double parametros[], double epslon1, double cl1);
double cl (double parametros[]);
double epslon (double parametros[], double ar1);
double ar (double parametros[]);

#endif
