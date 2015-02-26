#include "booleen.h"
#include "random.h"

#define TAILLE_GRILLE_X 50 //le nombre maximum de colonnes de la grille
#define TAILLE_GRILLE_Y 50 //le nombre maximum de lignes de la grille
#define TAILLE_SERIE_PARCOUR (TAILLE_GRILLE_Y*TAILLE_GRILLE_X)//le nombre d'elements maximum dans une serie des nombres randoms(pour donner l'ordre de parcour)
#define LONGUEUR_MAX_MOT 30
#define NOMBRE_MOT 100 //nombre de mots maximum dans la grille 
#define LONGUEUR_NOM_FICHIER 256

//definition de serie pour parcour
/**
 * \struct SerieParcourGrille
 * \brief tableau d'entiers
 *
 */
typedef int SerieParcourGrille[TAILLE_SERIE_PARCOUR];

/**
 * \struct SerieParcourDirection
 * \brief tableau d'entiers
 *
 */
typedef int SerieParcourDirection[8];

//definition de coordonnee
/**
 * \struct Coordonnee
 * \brief contient 2 entiers
 *
 */
typedef struct{
    int x;
    int y;
}Coordonnee;


//definition de mot
/**
 * \struct Mot
 * \brief chaine de caractères
 *
 */
typedef char Mot[LONGUEUR_MAX_MOT];


//definition de dictionnaire
/**
 * \struct Dict
 * \brief contient 2 chaines de caractères
 * 
 * il permet de stocker le nom et la référence du dictionnaire
 */
typedef struct{
    char nomDict[LONGUEUR_NOM_FICHIER];
    char refDict[LONGUEUR_NOM_FICHIER];
}Dict;

//definition du mot dans la grille
/**
 * \struct motDansGrille
 * \brief contient le mot, sa longueur et sa position
 *
 */
typedef struct{
    Mot mot;
    int longueur;//longueur de mot
    Coordonnee deb;//coordonnee au debut du mot
    Coordonnee fin;//coordonnee a la fin du mot
}motDansGrille; 


//definition de la grille
/**
 * \struct Grille
 * \brief contient toutes les informations concernant la grille
 * 
 * la structure contient la taille de la grille (longueur et largeur), laliste des mots placés dans la grille, le nombre de mots placés dans la grille et le tableau qui contient les lettres.
 *
 */
typedef struct{
    char tableau[TAILLE_GRILLE_Y][TAILLE_GRILLE_X];//pour contenir les lettres
    int tailleY;//nombre de lignes de la grille
    int tailleX;//nombre de colonnes de la grille
    motDansGrille listeMots[NOMBRE_MOT];//liste des mots dans la grille
    int nombreMots;//nombre des mots dans la grille
}Grille;

//definition de bitmap
/**
 * \struct Bitmap
 * \brief tableau d'entiers
 *
 */
typedef int Bitmap[TAILLE_GRILLE_Y][TAILLE_GRILLE_X];

//fonction pour generer une grille, X,Y signifie la taille de la grille, nomDict est le nom de dictionnaire,refDict est la reference de dictionnaire
Booleen genererGrille(Grille* g,int X,int Y,int nombre_mots,char* nomDict,char* refDict);

//fonction pour tester si les coordonnee envoyes par le client donnent un bon mot dans la grille
Booleen testerMot(Grille g,Coordonnee deb,Coordonnee fin);

//fonction pour generer les mots dans la grille
Booleen genererMots(Grille* g,int longueur_max,Dict* dict);

//fonction pour initialier le Bitmap de la grille
void initGrille(Grille* g,Bitmap bitmap);

//fonciton pour placer les mots dans le tableau de la grille
Booleen placerMots(Grille* g,int indice,Bitmap bitmap,SerieParcourGrille pG[NOMBRE_MOT],SerieParcourDirection pD[NOMBRE_MOT]);

//fonction pour traduire les lettres specials francais au lettre normalise(ca fonctione pas maintenant) et transformer lettre minuscul au lettre majuscul
char transLettre(char a);

//fonction pour tester si un mot peut se placer dans la grille selon coordonnees fixes
//si pouvoir se placer , placons-le 
Booleen essayerPlacer(Grille* g,int indice,Coordonnee deb,Coordonnee fin,Bitmap bitmap);

//fonction pour effacer un mot dans la grille 
void effacerMot(Coordonnee deb,Coordonnee fin,Bitmap bitmap);
