/**
 * \file refdict.c
 * \brief Programme pour 
 * \version 1.0
 * \date 23 mai 2012
 *
 * Programme pour generer un dictionnaire normalisé (trié par la longueur de mots) et un reference du dictionnaire normalisé qui enregistre les nombres de mots correspondants a certains longueurs maximales 
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=5){
        printf("Usage: refdict Nom_dict_entre Nom_dict_sorti Nom_reference Limite_inferieure_longueur\n");
        return EXIT_FAILURE;
    }
    FILE* entre_dict,*sorti_dict,*reference;
    entre_dict=fopen(argv[1],"r");
    sorti_dict=fopen(argv[2],"w");
    reference=fopen(argv[3],"w");
    int nombre_mot[40]={0};//nombre_mot[i] signifie qu'il y a nombre_mot[i] mots de longueur<=i
    int ligne_total=0;
    int le_plus_court=atoi(argv[4]);
    char mot[30];
    int max_longueur=0;
    //pour obtenir le longuer maximum de mots et le nombre des mots(ligne_total)
    while(fgets(mot,100,entre_dict)!=NULL){
        if(strstr(mot,"-"))continue;
        int l=strlen(mot)-1;
        if(l<le_plus_court)continue;
        if(l>max_longueur)max_longueur=l;
        ligne_total++;
    }
    fprintf(reference,"%d\n%d\n",ligne_total,max_longueur);
    //pour calculer les nombres de mots d'un longueur fixe
    int i;
    for(i=le_plus_court;i<=max_longueur;i++){
        fseek(entre_dict,0,SEEK_SET);
        while(fgets(mot,100,entre_dict)!=NULL){
            if(strstr(mot,"-"))continue;
            if(strlen(mot)-1!=i)continue;
            nombre_mot[i]++;
            fprintf(sorti_dict,"%s",mot);
        }
    }
    //sauvegarder les nombre
    for(i=1;i<=max_longueur;i++){
        nombre_mot[i]=nombre_mot[i]+nombre_mot[i-1];
        fprintf(reference,"%d %d\n",i,nombre_mot[i]);
    }
    return EXIT_SUCCESS;
}
