/**
 * \file grille.c
 * \brief Programme de génération.
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour générer la grille et placer les mots dans la grille.
 *
 */

#include "grille.h"
#include <stdio.h>
#include <string.h>



//fonction pour generer les mots dans la grille
/**
 * \fn Booleen genererMots(Grille* g,int longueur_max,Dict* dict)
 * 
 * \param g objet de type grille qui contient les lettres, les mots et la taille de la grille
 * \param longueur_max c'est un entier qui représente la longueur maximale que peut prendre un mot
 * \param dict c'est le dictionnaire qui comprend tous les mots
 * 
 * \return retourne vrai en cas de réussite
 * 
 */
Booleen genererMots(Grille* g,int longueur_max,Dict* dict){
    if(NOMBRE_MOT<g->nombreMots)return FAUX;
    FILE* fp_dict=fopen(dict->nomDict,"r");
    FILE* fp_ref=fopen(dict->refDict,"r");
    int serie_random[NOMBRE_MOT];
    int total_ligne,fin;
    fscanf(fp_ref,"%d",&total_ligne);
    int maxl_dict;
    fscanf(fp_ref,"%d",&maxl_dict);
    int i;
    while(fscanf(fp_ref,"%d%d",&i,&fin)!=EOF && i<longueur_max);
    if(!serieRandom(1,fin,serie_random,g->nombreMots)){
        return FAUX;
    }
    int count_ligne=0;
    Mot m;
    int count=0;
    while(count<g->nombreMots && fgets(m,100,fp_dict)!=NULL){
        count_ligne++;
        if(dansTableau(count_ligne,serie_random,g->nombreMots)){
            strcpy(g->listeMots[count].mot,m);
            g->listeMots[count].mot[strlen(m)-1]='\0';
            g->listeMots[count].longueur=strlen(m)-1;
            count++;
        }
    }
    fclose(fp_dict);
    fclose(fp_ref);
    return VRAI;
}


/**
 * \fn void initGrille(Grille* g,Bitmap bitmap)
 * 
 * \param g objet de type grille qui contient les lettres, les mots et la taille de la grille
 * \param bitmap objet type bitmap
 *  
 * \return retourne la grille initialisée
 * 
 */
void initGrille(Grille* g,Bitmap bitmap){
    int i,j;
    srand(time(NULL));
    for(i=0;i<TAILLE_GRILLE_X;i++){
        for(j=0;j<TAILLE_GRILLE_Y;j++){
            bitmap[j][i]=0;
            g->tableau[j][i]='A'+randIntervalle(0,25);
        }
    }
}

//fonction pour transformer lettre francais special et transformer lettre minuscul au lettre majuscul
/**
 * \fn char transLettre(char a)
 * 
 * \param a type char
 *  
 * \return une lettre majuscule sans accent
 * 
 */
char transLettre(char a){
    if(a>='a'&&a<='z')return (a+'A'-'a');
    if(a>='A'&&a<='Z')return a;
    return a;
}

//fonction pour generer la grille
/**
 * \fn Booleen genererGrille(Grille* g,int X,int Y,int nombre_mots,char* nomDict,char* refDict)
 * 
 * \param g objet de type grille qui contient les lettres, les mots et la taille de la grille
 * \param nombre_mots entier:nombre de mots qu'il y aura dans la grille
 * \param X entier : largeur de la grille
 * \param Y entier : longueur de la grille
 * \param nomDict chaine de caractères: nom du dictionnaire qu'il faut ouvrir
 * \param refDict chaine de caractères : référence du dictionnaire qu'il faut ouvrir
 *  
 * \return retourne la grille avec les mots
 * 
 */
Booleen genererGrille(Grille* g,int X,int Y,int nombre_mots,char* nomDict,char* refDict){
    int max_X_Y=X>Y?X:Y;
    if(nombre_mots>NOMBRE_MOT||nombre_mots>max_X_Y){
        printf("Trop de mots demandes!\n");
        return FAUX;
    }
    if(X>TAILLE_GRILLE_X||Y>TAILLE_GRILLE_Y){
        printf("Taille demandee est trop grande!");
        return FAUX;
    }
    g->nombreMots=nombre_mots;
    g->tailleY=Y;
    g->tailleX=X;
    int longueur_max=X<Y?X:Y;//longueur maximum de mots
    Dict dict;
    strcpy(dict.nomDict,nomDict);
    strcpy(dict.refDict,refDict);
    genererMots(g,longueur_max,&dict);//generer les mots dans la grille
    //generer les series randoms pour parcours
    SerieParcourGrille parcourGrille[NOMBRE_MOT];
    SerieParcourDirection parcourDirection[NOMBRE_MOT];
    int i;
    for(i=0;i<g->nombreMots;i++){
        serieRandom(0,Y*X-1,parcourGrille[i],Y*X);
        serieRandom(0,7,parcourDirection[i],8);
    }
    Bitmap bitmap;
    initGrille(g,bitmap);
    return placerMots(g,0,bitmap,parcourGrille,parcourDirection);
}

//fonction pour placer les mots dans le tableau de la grille
/**
 * \fn Booleen placerMots(Grille* g,int indice,Bitmap bitmap,SerieParcourGrille pG[NOMBRE_MOT],SerieParcourDirection pD[NOMBRE_MOT])
 * 
 * \param g objet de type grille qui contient les lettres, les mots et la taille de la grille
 * \param bitmap objet type bitmap
 * \param pG tableau d'entiers : série d'indices pour parcourir la grille
 * \param pD tableau d'entiers à 2 dimensions qui contient toutes les directions possibles
 * \param indice entier : indice du mot choisit dans la liste
 *  
 * \return retourne vrai si le mot est bien placé
 * 
 */
Booleen placerMots(Grille* g,int indice,Bitmap bitmap,SerieParcourGrille pG[NOMBRE_MOT],SerieParcourDirection pD[NOMBRE_MOT]){
    if(indice>=g->nombreMots)return VRAI;
    int direction[8][2]={
        {0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}
    };
    int i,j;
    int XY=g->tailleY*g->tailleX;
    for(i=0;i<XY;i++){
        for(j=0;j<8;j++){
            Coordonnee deb,fin;
            deb.x=pG[indice][i]%g->tailleX;
            deb.y=pG[indice][i]/g->tailleX;
            fin.x=deb.x+direction[pD[indice][j]][0]*(g->listeMots[indice].longueur-1);
            fin.y=deb.y+direction[pD[indice][j]][1]*(g->listeMots[indice].longueur-1);
            if(fin.x<0||fin.x>=g->tailleX||fin.y<0||fin.y>=g->tailleY){
                continue;
            }
            if(essayerPlacer(g,indice,deb,fin,bitmap)){
                if(placerMots(g,indice+1,bitmap,pG,pD)){
                    return VRAI;
                }
                else{
                    effacerMot(deb,fin,bitmap);
                }
            }
        }
    }
    return FAUX;
}


/**
 * \fn Booleen essayerPlacer(Grille* g,int indice,Coordonnee deb,Coordonnee fin,Bitmap bitmap)
 * 
 * \param g objet de type grille qui contient les lettres, les mots et la taille de la grille
 * \param bitmap objet type bitmap
 * \param indice entier : indice du mot choisi dans la liste
 * \param deb coordonnées de la première lettre du mot
 * \param fin coordonnées de la dernière lettre du mot
 *  
 * \return retourne vrai si la place  choisie pour le mot est vide ou que la place non libre correspond à la même lettre pour les 2 mots
 * 
 */
Booleen essayerPlacer(Grille* g,int indice,Coordonnee deb,Coordonnee fin,Bitmap bitmap){
    Mot m;
    strcpy(m,g->listeMots[indice].mot);
    int xvar=(deb.x>fin.x)?-1:1;
    if(deb.x==fin.x)xvar=0;
    int yvar=(deb.y>fin.y)?-1:1;
    if(deb.y==fin.y)yvar=0;
    int x=deb.x,y=deb.y;
    int i=0;
    while(i<strlen(m)){
        if(bitmap[y][x]>0 && transLettre(m[i])!=g->tableau[y][x]){
            return FAUX;
        }
        i++;
        x+=xvar;
        y+=yvar;
    }
    x=deb.x;y=deb.y;i=0;
    while(i<strlen(m)){
        g->tableau[y][x]=transLettre(m[i]);
        bitmap[y][x]+=1;
        i++;
        x+=xvar;
        y+=yvar;
    }
    g->listeMots[indice].deb=deb;
    g->listeMots[indice].fin=fin;
    return VRAI;
}

/**
 * \fn void effacerMot(Coordonnee deb,Coordonnee fin,Bitmap bitmap)
 * 
 * \param bitmap objet type bitmap
 * \param deb coordonnées de la première lettre du mot
 * \param fin coordonnées de la dernière lettre du mot
 *  
 * \return retourne un void : efface le mot dans la grille une fois qu'il a été trouvé
 */
void effacerMot(Coordonnee deb,Coordonnee fin,Bitmap bitmap){
    int xvar,yvar;
    if(deb.x<fin.x)xvar=1;
    else if(deb.x>fin.x)xvar=-1;
    else xvar=0;
    if(deb.y<fin.y)yvar=1;
    else if(deb.y>fin.y)yvar=-1;
    else yvar=0;
    int x=deb.x,y=deb.y;
    while(!(x==fin.x+xvar && y==fin.y+yvar)){
        bitmap[y][x]-=1;
    }
}
