#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 100


/**
 * \struct Score
 * \brief contient le nom et le score du joueur
 *
 */
struct Score {
    char nom[TAILLE_MAX];
    int score;
};

void afficherScore(FILE* f);//Affiche ce qui est écrit dans le fichier score.txt
void ajouterScore(FILE* f, char nom[], int score);//Lit le fichier, utilise trierTableau et réécrit le fichier score.txt pour le mettre à jour
void trierTableau(struct Score* listScore, char nom[], int score);//Ajoute un score dans le tableau en s'assurant qu'il soit à la bonne position
void lowestScore(FILE* f);//show lowest score
