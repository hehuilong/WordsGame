#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"
#define NOMBRE_MENU (4)

char* menu[NOMBRE_MENU]={
    "1.generer les mots",
    "2.tester le module random",
    "3.generer grille",
    "0.sortir"
};

int main(){
    while(1){
        int i;
        for(i=0;i<NOMBRE_MENU;i++)printf("%s\n",menu[i]);
        int n;
        scanf("%d",&n);
        if(n==0)break;
        if(n==1){
            int nombre_mots;
            printf("Saisir le nombre de mots:");
            scanf("%d",&nombre_mots);
            printf("Saifir le longueur max de mots:");
            int maxl;
            scanf("%d",&maxl);
            Grille g;
            g.nombreMots=nombre_mots;
            Dict dict={"dict_e","ref_dict_e"};
            genererMots(&g,maxl,&dict);
            for(i=0;i<nombre_mots;i++){
                printf("%s %d\n",g.listeMots[i].mot,g.listeMots[i].longueur);
            }
        }
	    if(n==2){
            int deb,fin,taille,serie[200];
            printf("Saisir le nombre au debut(<200):");
            scanf("%d",&deb);
            printf("\nSaisir le nombre a la fin(<200,>deb):");
            scanf("%d",&fin);
            printf("\nSaisir la taille de serie:(<=fin-deb+1):");
            scanf("%d",&taille);
            serieRandom(deb,fin,serie,taille);
            printf("\nserie genere:\n");
            for(i=0;i<taille;i++)printf("%d ",serie[i]);
            printf("\n");
        }
        if(n==3){
            printf("Saisir taille x y: ");
            int x,y;
            scanf("%d %d",&x,&y);
            printf("Saisir nombre de mots:");
            int n;
            scanf("%d",&n);
            Grille g;
            if(!genererGrille(&g,x,y,n,"dict_e","ref_dict_e"))continue;
            int i,j;
            printf("================\n");
            printf("   ");
            for(i=0;i<g.tailleX;i++)printf("%2d",i);
            printf("\n");
            for(i=0;i<g.tailleY;i++){
                printf("%3d",i);
                for(j=0;j<g.tailleX;j++){
                    printf("%2c",g.tableau[i][j]);
                }
                printf("\n");
            }
            printf("================\n");
            printf("Liste mots:\n");
            for(i=0;i<g.nombreMots;i++){
                printf("%s %d\n",g.listeMots[i].mot,g.listeMots[i].longueur);
                printf("Coordonnees: from (%d,%d)to (%d %d)\n",g.listeMots[i].deb.x,g.listeMots[i].deb.y,g.listeMots[i].fin.x,g.listeMots[i].fin.y);
            }
            printf("================\n");
        }
    }
    return EXIT_SUCCESS;
}
