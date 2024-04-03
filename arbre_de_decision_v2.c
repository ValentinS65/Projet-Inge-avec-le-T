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
    for(int i=1;i<s.nbr_exemples;i++){
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
    printf("nbr attributs : %d\n",s.nbr_attributs);
    printf("nbr exemples : %d\n",s.nbr_exemples);
    printf("nbr mots : %d\n",nbr_mots);
    printf("nbr lignes : %d\n",nbr_lignes);
    tableau=malloc(sizeof(char **)*nbr_lignes); //On initialise notre tableau de chaine de caractère
    if (tableau == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for(i=0;i<nbr_lignes;i++){ //On recupere les donnees du fichier
        tableau[i]=malloc(sizeof(char*)*s.nbr_attributs); 
        if (tableau[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for(j=0;j<s.nbr_attributs+1;j++){ 
            tableau[i][j]=malloc(sizeof(char)*20);
            if (tableau[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
            pos=0;
            while((c= fgetc(fd))!=' ' && c!='\n' && c!='\0' && c!=EOF && pos<19 && c!='\r'){
                if(i==1 && j==5){
                //printf("pos:%d mot:%c\n",pos,c);
                }
                tableau[i][j][pos]=c;
                //printf("pos:%d mot:%s\n",pos,tableau[i][j]);
                pos++;
            }
            //printf("i:%d,j:%d:%s\n",i,j,tableau[i][j]);

            tableau[i][j][pos]='\0';
            if(c=='\n'){
                break;
            }            
        }
    }
    fclose(fd);
    s.tableau=tableau;
    s.liste_etiquette=cherche_etiquette(s);
    s.liste_attributs_dispo=tableau[0];
    return s;
}


void afficher_tableau(stockage s){ 
    for(int i=0;i<s.nbr_exemples+1;i++){
        for(int j=0;j<s.nbr_attributs;j++){
                printf("%s ",s.tableau[i][j]);
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
    //afficher_etiquette(e);
    //free_stockage(&e);
}