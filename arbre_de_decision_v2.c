#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char ** extraction_fichier(FILE fichier){
    int nbr_lignes=0,nbr_mots=0,i=0,j=0,pos=0;
    char c;
    char mot[20];
    char ** tableau;
    FILE * fd=open(fichier,"r");
    //on calcule le nombre de ligne et le nombre de mot de la premiere ligne pour malloc notre tableau
    while(EOF){
        c=fgetc(fd)
        if(nbr_lignes==0 && c==' '){
            nbr_mots++;
        }
        if(c=='\n'){
            nbr_lignes++;
        }
    }
    rewind(fd);
    //On revient au debut du fichier
    tableau=malloc(sizeof(char *)*nbr_lignes); //On initialise notre tableau de chaine de caractère
    for(i=0;i<nbr_lignes;i++){
        tableau[i]=malloc(sizeof(char)*nbr_mots+1); //On rajoute 1 pour les etiquettes
    }  
    while(EOF){ //On recupere les donnees du fichier
        for(j=0;j<nbr_mots;j++){
            c=fgetc(fd);
            pos=0;
            while(c!=' '){
                mot[pos]=c;
                c=fgetc(fd);
                pos++;
            }
            tableau[i][j]=mot;
        }
        i++;
    }
    return tableau;

}

int main(){
    char ** e=extraction_fichier("test.txt");
    printf("%s"e[0][0]);
}