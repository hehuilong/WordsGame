#include<time.h>
#include<stdlib.h>
#include "booleen.h"

//fonction pour echanger deux entiers
void swap(int* a,int* b);

//fonction pour generer un nombre random entier dans l'intervalle [deb,fin]
int randIntervalle(int deb,int fin);

//fonction pour generer un serie des nombres random dans l'intervalle [deb,fin], les elements dans la serie est tout unique, il n'y a pas duplicite
Booleen serieRandom(int deb,int fin,int*serie,int taille_serie);

//fonction pour tester si un entier est dans un tableau d'entiers
Booleen dansTableau(int n,int* tableau,int taille_tableau);
