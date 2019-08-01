


#if !defined(UTILS_H_INCLUDED)
#define UTILS_H_INCLUDED

#include "windows.h"
#define NB_ELEMENT(tab) (sizeof(tab)/sizeof(tab[0]))


void initrandom(int seed); 
// nb aleatoire entre a et b inclu
int    randomval(int a   , int b); 
double randomval(double a, double b);

// arrondi à l'entier le + proche
// plus rapidement que ((int)(floor(x+0.5))) 
int fltround_to_int(double x);


HWND ShowConsoleWindow(BOOL on);


#endif // defined(UTILS_H_INCLUDED)