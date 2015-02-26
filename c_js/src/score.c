/**
 * \file score.c
 * \brief Programme pour trier et sauvegarder les scores
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour trier et sauvegarder les scores
 *
 */



#include "score.h"
#include <string.h>
/*int main()
{
    FILE* f = NULL;
    char nom[TAILLE_MAX] = "vuuk";
    ajouterScore(f, nom, 0);
    afficherScore(f);

    return 0;
}*/


 /**
  * \fn void ajouterScore(FILE* f, char nom[], int score)
  * 
  * \param f type file qui contient la liste des scores
  * \param nom chaine de caractère qui contient le nom du joueur
  * \param score entier qui contient le score du joueur
  *
  * \return retourne un void : ajoute un score au fichier f si il fait partie des 10 premiers
  */
void ajouterScore(FILE* f, char nom[], int score)
{
    f = fopen("score.txt", "r");
    struct Score listScore[10];
    int i=0;
    char ligne[TAILLE_MAX];
    if(f != NULL)
    {
        while (fgets(ligne, TAILLE_MAX, f) != NULL)
        {
            sscanf(ligne, "%s : %d\n", listScore[i].nom, &listScore[i].score);
            i++;
        }
        trierTableau(listScore, nom, score);
        printf("\n");


    }
    else
        printf("Erreur lors de l'ouverture du fichier de score\n");
    fclose(f);
    f=fopen("score.txt","w");
    if(f != NULL)
    {
        for(i=0; i<10; i++)
            {
                fprintf(f, "%s : %d\n", listScore[i].nom, listScore[i].score);
                //printf("%s : %d\n", listScore[i].nom, listScore[i].score);
            }

    }
    else
        printf("Erreur lors de l'ouverture du fichier de score");
    fclose(f);
}



 /**
  * \fn void trierTableau(struct Score *listScore, char nom[], int score)
  * 
  * \param listScore type Score contient le nom et le score du joueur
  * \param nom chaine de caractère qui contient le nom du joueur
  * \param score entier qui contient le score du joueur
  *
  * \return retourne un void : trie les scores
  */
void trierTableau(struct Score *listScore, char nom[], int score)
{
    int i=0;
    if(score > listScore[9].score)
    {
        for(i=0; i < 10; i++)
        {
            if(score > listScore[i].score)
            {
                struct Score aux;
                aux.score = listScore[i].score;
                strcpy(aux.nom, listScore[i].nom);
                strcpy(listScore[i].nom, nom);
                listScore[i].score = score;
                strcpy(nom, aux.nom);
                score = aux.score;
            }
        }
    }

}

 /**
  * \fn void afficherScore(FILE* f)
  * 
  * \param f type file qui contient la liste des scores
  * 
  * \return retourne un void : affiche les scores
  */
void afficherScore(FILE* f)
{
    f = fopen("score.txt", "r");
    char ligne[TAILLE_MAX];
    //printf("Afficher le tableau :\n");
    if(f!=NULL)
        while (fgets(ligne, TAILLE_MAX, f) != NULL)
        {
            printf("%s#", ligne);
        }
    else
        printf("Erreur lors de l'ouverture du fichier de score");
    printf("\n");
    fclose(f);
}


 /**
  * \fn void lowestScore(FILE* f)
  * 
  * \param f type file qui contient la liste des scores
  * 
  * \return retourne un void : affiche le score le plus bas
  */
void lowestScore(FILE* f)
{
    f = fopen("score.txt", "r");
    char ligne[TAILLE_MAX];
    char result[TAILLE_MAX];
    //printf("Afficher le tableau :\n");
    if(f!=NULL)
        while (fgets(ligne, TAILLE_MAX, f) != NULL)
        {
            strcpy(result,ligne);
        }
    else
        printf("Erreur lors de l'ouverture du fichier de score");
    printf("%s", result);
    fclose(f);
}
