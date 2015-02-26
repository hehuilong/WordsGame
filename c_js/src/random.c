/**
 * \file random.c
 * \brief Programme pour gérer tous les tirages aléatoires
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour gérer tous les tirages aléatoires
 *
 */



#include "random.h"
#include<stdio.h>


/** 
 * \fn void swap (int* a,int* b)
 * \param a pointeur sur entier
 * \param b pointeur sur entier
 *
 * \return retourne void : échange la valeur de 2 variables
 */
void swap (int* a,int* b){
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}



/** 
 * \fn int randIntervalle(int deb,int fin)
 * \param deb entier
 * \param fin entier
 *
 * \return retourne une valeur au hasard dans l'intervalle donné en paramètres
 */
int randIntervalle(int deb,int fin){
    return ( rand()%(fin-deb+1)+deb );
}

//fonction pour tester si un entier est dans un tableau d'entiers
/** 
 * \fn Booleen dansTableau(int n,int* tableau,int taille_tableau)
 * \param n entier
 * \param tableau tableau d'entiers
 * \param taille_tableau entier
 * 
 * \return retourne vrai si n est dans le tableau
 */
Booleen dansTableau(int n,int* tableau,int taille_tableau){
    int i;
    for(i=0;i<taille_tableau;i++){
        if(tableau[i]==n)return VRAI;
    }
    return FAUX;
}




/** 
 * \fn Booleen serieRandom(int deb,int fin,int* serie,int taille_serie)
 * 
 * \param deb entier
 * \param fin entier
 * \param serie tableau d'entiers
 * \param taille_série entier
 * 
 * \return retourne vrai si on a pu générer une liste d'entiers de taille taille_serie sans duplicité
 */
Booleen serieRandom(int deb,int fin,int* serie,int taille_serie){
    srand(time(NULL));
    if(taille_serie==fin-deb+1){
        int i;
        for(i=0;i<=fin-deb;i++){
            serie[i]=deb+i;
        }
        for(i=0;i<fin-deb;i++){
            int pourSwap=randIntervalle(i,fin-deb);
            swap(&serie[i],&serie[pourSwap]);
        }
        return VRAI;
    }
    else if(taille_serie<fin-deb+1){
        int i;
        for(i=0;i<taille_serie;i++){
            int r;
            while(dansTableau( (r=randIntervalle(deb,fin)) ,serie,i ));
            serie[i]=r;
        }
        return VRAI;
    }
    else{
        printf("Impossible de generer serie random sans duplicite\n");
        return FAUX;
    }
}
