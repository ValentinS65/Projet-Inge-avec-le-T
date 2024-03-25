
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct stockage{
    char *** tableau;
    char ** liste_attributs_dispo;
    char ** liste_etiquette;
    int nbr_attributs;
    int nbr_exemples;
}stockage;


stockage extraction_fichier(char * fichier){
    stockage s;
    int nbr_lignes=0,nbr_mots=0,i=0,j=0,pos=0;
    char c;
    char* mot;
    char *** tableau;
    FILE * fd= fopen(fichier,"r");
    //on calcule le nombre de ligne et le nombre de mot de la premiere ligne pour malloc notre tableau
    c=fgetc(fd);
    while(c != EOF){
        
        if(nbr_lignes==0 && c==' '){
            nbr_mots++;
        }
        if(c=='\n'){
            nbr_lignes++;
        }
        c=fgetc(fd);
    }
    rewind(fd);
    //On revient au debut du fichier
    tableau=malloc(sizeof(char **)*nbr_lignes); //On initialise notre tableau de chaine de caractère
    for(i=0;i<nbr_lignes;i++){
        tableau[i]=malloc(sizeof(char*)*nbr_mots+1); //On rajoute 1 pour les etiquettes
    }  
    for(i=0;i<nbr_lignes;i++){ //On recupere les donnees du fichier
        for(j=0;j<nbr_mots;j++){
            mot=malloc(sizeof(char)*20);
            c=fgetc(fd);
            pos=0;
            while(c!=' ' && c!='\n'){
                mot[pos]=c;
                c=fgetc(fd);
                pos++;
                printf("mot :%s ",mot);
            }
            mot[pos]='\n';
            tableau[i][j]=strdup(mot);
            free(mot);
        }
        i++;
    }
    s.tableau=tableau;
    fclose(fd);
    s.nbr_exemples=nbr_lignes;
    s.nbr_attributs=nbr_mots;
    return s;

}

void free_tableau(char ***tableau, int nbr_lignes, int nbr_mots) {
    for (int i = 0; i < nbr_lignes; i++) {
        for (int j = 0; j < nbr_mots; j++) {
            free(tableau[i][j]);
        }
        free(tableau[i]);
    }
    free(tableau);
}

void free_stockage(stockage *s) {
    free_tableau(s->tableau, s->nbr_exemples, s->nbr_attributs);
    free(s->liste_attributs_dispo);
    free(s->liste_etiquette);
}


int main(){
    stockage e=extraction_fichier("test.txt");
    printf("%s",e.tableau[0][1]);
    free_stockage(&e);
}