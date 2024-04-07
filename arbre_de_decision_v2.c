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
    int nbr_etiquette;
}stockage;

typedef struct attribut{
    char *** tableau;
    int * nbr_valeur_attribut;
    int ** nbr_apparition;

}attribut;


int inList(char ** l, char * mot,int taille){
    for(int i=0;i<taille;i++){
        if(strcmp(mot,l[i])==0){
            return 1;
        }
    }
    return 0;
}

char ** cherche_etiquette(stockage *s){
    int pos=0;
    char ** liste_etiquette=malloc(sizeof(char*)*s->nbr_exemples);
    for(int i=1;i<s->nbr_exemples+1;i++){
        if(inList(liste_etiquette,s->tableau[i][s->nbr_attributs-1],pos)==0){ //On vérifie qu'on ajoute uniquement les etiquettes qui ne sont pas présent dans notre liste grâce à la fonction inList
            liste_etiquette[pos]=s->tableau[i][s->nbr_attributs-1];
            //printf("etiquette: %s\n",s.tableau[i][s.nbr_attributs-1]);
            s->nbr_etiquette++;
        printf("nbr_etiquette i:%d\n",s->nbr_etiquette);

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
    s.nbr_etiquette=0;
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
    s.liste_etiquette=cherche_etiquette(&s);
    s.liste_attributs_dispo=malloc(sizeof(char*)*s.nbr_attributs-2); //-2 car on enleve l'etiquette
     if (s.liste_attributs_dispo == NULL) {
        fprintf(stderr, "Memory allocation failed for liste_attributs_dispo.\n");
        exit(1);
    }
    for(i=0;i<s.nbr_attributs-1;i++){
        s.liste_attributs_dispo[i]=malloc(sizeof(char)*20);
        if (s.liste_attributs_dispo[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for attribute name.\n");
            exit(1);
        }
        s.liste_attributs_dispo[i] = strdup(s.tableau[0][i]);
        printf("%s\n",s.liste_attributs_dispo[i]);

    }

    fclose(fd);
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
    printf("nbr_etiquette i:%d\n",s.nbr_etiquette);

    for(int i=0;i<s.nbr_etiquette;i++){
        printf("etiquette i:%d,%s\n",i,s.liste_etiquette[i]);
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

void free_stockage(stockage s) {

    free_tableau(s.tableau, s.nbr_exemples+1, s.nbr_attributs);
    for (int i=0;i<s.nbr_attributs-1;i++){
        printf("%s\n",s.liste_attributs_dispo[i]);
        free(s.liste_attributs_dispo[i]);
    }
    free(s.liste_attributs_dispo);
    for (int i = 0; i < s.nbr_etiquette+1; i++) {
        free(s.liste_etiquette[i]);
    }
    free(s.liste_etiquette);
}

// Calcul de gain d'entropie

//Recupération des valeurs possibles pour chaque attribut.
attribut Valeur_Attribut(stockage s){
    char *** tableau=malloc(sizeof(char**)*s.nbr_exemples+1);
    int * count=malloc(sizeof(int)*s.nbr_attributs);
    int **nbr_apparition=malloc(sizeof(int*)*s.nbr_attributs);
   //On initialise notre tableau de chaine de caractère
    if (tableau == NULL ||count==NULL || nbr_apparition==NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for(int i=0;i<s.nbr_exemples;i++){ //On recupere les donnees du fichier
        tableau[i]=malloc(sizeof(char*)*s.nbr_attributs); 
        
        if (tableau[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for(int j=0;j<s.nbr_attributs+1;j++){ 
            tableau[i][j]=NULL;
            nbr_apparition[j]=calloc(s.nbr_exemples,sizeof(int));
        }
    }
    // Parcourir chaque attribut
    for (int i = 0; i < s.nbr_attributs - 1; i++) {
        int index = 0; // Index pour stocker les valeurs uniques

        // Parcourir chaque exemple pour récupérer les valeurs uniques
        for (int j = 1; j < s.nbr_exemples + 1; j++) {
            char *valeur = s.tableau[j][i]; // Valeur de l'attribut dans cet exemple

            // Vérifier si cette valeur existe déjà dans les valeurs attributs
            int exist = 0;
            for (int k = 0; k < index; k++) {
                if (strcmp(valeur, tableau[i][k]) == 0) {
                    exist = 1; // La valeur existe déjà
                    nbr_apparition[i][k]++;
                    break;
                }
            }

            // Si la valeur n'existe pas déjà, l'ajouter
            if (!exist) {
                tableau[i][index] = strdup(valeur);
                nbr_apparition[i][index]=1;
                index++;
            }
        }
        count[i]=index-1;
    }
    attribut attrib;
    attrib.nbr_valeur_attribut=count;
    attrib.tableau=tableau;
    attrib.nbr_apparition=nbr_apparition;
    return attrib;
}

//Libere la mémoire de attribut
void free_attribut(attribut a, stockage s) {
    // Libération de la mémoire allouée pour le tableau de valeurs
    for (int i = 0; i < s.nbr_attributs; i++) {
        for (int j = 0; j < s.nbr_exemples; j++) {
            free(a.tableau[i][j]);
        }
        free(a.tableau[i]);
    }
    free(a.tableau);

    // Libération de la mémoire allouée pour le tableau de nombre d'apparition
    for (int i = 0; i < s.nbr_attributs; i++) {
        free(a.nbr_apparition[i]);
    }
    free(a.nbr_apparition);

    // Libération de la mémoire allouée pour le tableau de nombre de valeurs attributaires
    free(a.nbr_valeur_attribut);
}

//Calcul de l'entropie
float entropie(int *nbr_apparition, int nbr_valeurs) {
    float entropie = 0.0;
    float total = 0.0;
    for (int i = 0; i < nbr_valeurs; i++) {
        total += nbr_apparition[i];
    }
    for (int i = 0; i < nbr_valeurs; i++) {
        float prob = (float) nbr_apparition[i] / total;
        if (prob != 0.0) {
            entropie -= prob * log2(prob);
        }
    }
    return entropie;
}
//Calcul du gain entropique
float gain(attribut attr, stockage s, int set) {
    float gain_entropique = 0.0;
    float entropie_totale = entropie(attr.nbr_apparition[set], s.nbr_etiquette);
    for (int i = 0; i < attr.nbr_valeur_attribut[set]; i++) {
        float prob_valeur = (float) attr.nbr_apparition[set][i] / s.nbr_exemples;
        float entropie_sous_ensemble = entropie(attr.nbr_apparition[i], attr.nbr_valeur_attribut[set]);
        gain_entropique += prob_valeur * entropie_sous_ensemble;
    }
    gain_entropique = entropie_totale - gain_entropique;
    return gain_entropique;
}





int main(){
    stockage e=extraction_fichier("test.txt");
    //attribut a=Valeur_Attribut(e);
    //afficher_tableau(e);
    //afficher_etiquette(e);
    //free_attribut(a,e);
    //free_stockage(e);
    
}