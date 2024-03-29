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

int inList(char ** l, char * mot,int taille){
    for(int i=0;i<taille;i++){
        if(strcmp(mot,l[i])==0){
            return 1;
        }
    }
    return 0;

}

char ** cherche_etiquette(stockage s){
    int pos=0;
    char ** liste_etiquette=malloc(sizeof(char*)*s.nbr_exemples);
    for(int i=1;i<s.nbr_exemples;){
        if(inList(liste_etiquette,s.tableau[i][s.nbr_attributs],pos)==0){
            liste_etiquette[pos]=s.tableau[i][s.nbr_attributs];
            pos++;
        }
    }
    return liste_etiquette;
}


stockage extraction_fichier(char * fichier){
    stockage s;
    int nbr_lignes=0,nbr_mots=0,i=0,j=0,pos=0;
    char c;
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
    s.nbr_attributs=nbr_mots+1;
    s.nbr_exemples=nbr_lignes-1;
    //On revient au debut du fichier
    tableau=malloc(sizeof(char **)*nbr_lignes); //On initialise notre tableau de chaine de caractère
    for(i=0;i<nbr_lignes;i++){ //On recupere les donnees du fichier
        tableau[i]=malloc(sizeof(char*)*nbr_mots+2); //On rajoute 1 pour les etiquettes
        for(j=0;j<=nbr_mots+1;j++){
            tableau[i][j]=malloc(sizeof(char)*20);
            //printf(" c1:%c ",c);
            pos=0;
            while((c= fgetc(fd))!=' ' && c!='\n' && c!='\0' && c!=EOF && pos<=20){
                tableau[i][j][pos]=c;
                pos++;
                //printf(" c2:%c ",c);
            }
            //printf("i:%d j:%d,nbr_mots:%d\n",i,j,nbr_mots);
            tableau[i][j][pos]='\0';
            if(c=='\n'){
                j=nbr_mots+2;
            }
        }
    }
    s.tableau=tableau;
    s.liste_etiquette=cherche_etiquette(s);
    s.liste_attributs_dispo=tableau[0];
    fclose(fd);

    return s;

}


void afficher_tableau(stockage s){
    for(int i=0;i<=s.nbr_exemples;i++){
        for(int j=0;j<=s.nbr_attributs-1;j++){
            printf(" %s",s.tableau[i][j]);
            }
        printf("\n");
    }
    printf("nbr attributs : %d\n",s.nbr_attributs);
    printf("nbr exemples : %d\n",s.nbr_exemples);

}
void afficher_etiquette(stockage s){
    for(int i=0;i<s.nbr_exemples;i++){
        printf("%s ",s.liste_etiquette[i]);
    }
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
    for (int i=0;i<s->nbr_attributs;i++){
        free(s->liste_attributs_dispo[i]);
    }
    free(s->liste_attributs_dispo);
    
    for (int i = 0; i < s->nbr_exemples; i++) {
        free(s->liste_etiquette[i]);
    }
    free(s->liste_etiquette);
}

int main(){
    stockage e=extraction_fichier("test.txt");
    afficher_tableau(e);
    afficher_etiquette(e);
    //free_stockage(&e);
}