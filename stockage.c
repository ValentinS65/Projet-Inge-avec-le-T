#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stockage.h"


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
            liste_etiquette[pos]=strdup(s->tableau[i][s->nbr_attributs-1]);
            //printf("etiquette: %s\n",s.tableau[i][s.nbr_attributs-1]);
            s->nbr_etiquette++;
        printf("nbr_etiquette i:%d\n",s->nbr_etiquette);

            pos++;
        }
    }
    return liste_etiquette;
}

int notInList(int i,int j,stockage s,int * dejaVu, int taille){
    for(int k=0;k<taille;k++){
        //printf("la comparaison passe pour k= %d,i=%d et j=%d\n",k,i,j);
        //printf("comparaison entre %s et %s\n",s.tableau[dejaVu[k]][i],s.tableau[j][i]);
        if(strcmp(s.tableau[dejaVu[k]][i],s.tableau[j][i])==0){
           // printf("on retourne 0\n");
            return 0;
        }
    }
    //printf("on retourne 1\n");
    
    return 1;
}


int cherche_valeur_max(stockage s){
    int max=0;
    int taille=0;
    for(int i=0;i<s.nbr_attributs;i++){
        int * dejaVu=malloc(sizeof(int)*s.nbr_exemples);
        for(int j=1;j<s.nbr_exemples+1;j++){
            if(taille==0 || notInList(i,j,s,dejaVu,taille)==1){
                dejaVu[taille]=j;
                //printf("dejaVu %d taille %d\n",dejaVu[taille],taille);
                taille++;

            }
        }
        if(taille>max){
            max=taille;
        }
        free(dejaVu);
        taille=0;
    }
    return max;
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
    s.nbr_exemples=nbr_lignes;
    s.nbr_etiquette=0;
    //On revient au debut du fichier
    printf("nbr attributs : %d\n",s.nbr_attributs);
    printf("nbr exemples : %d\n",s.nbr_exemples);
    printf("nbr mots : %d\n",nbr_mots);
    printf("nbr lignes : %d\n",nbr_lignes+1);
    tableau=malloc(sizeof(char **)*(s.nbr_exemples+1)); //On initialise notre tableau de chaine de caractère
    if (tableau == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for(i=0;i<nbr_lignes+1;i++){ //On recupere les donnees du fichier
        tableau[i]=malloc(sizeof(char*)*(s.nbr_attributs+1));  //On ajoute 1 pour garder un espace pour le "signal" d'arret (c'est pour le pc)
        if (tableau[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for(j=0;j<s.nbr_attributs+1;j++){ 
            tableau[i][j]=malloc(sizeof(char)*30);
            if(tableau[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
            pos=0;
            while((c= fgetc(fd))!=' ' && c!='\n' && c!='\0' && c!=EOF && pos<29 && c!='\r'){
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
    s.tableau=tableau;
    s.liste_etiquette=cherche_etiquette(&s);
    s.liste_attributs_dispo=malloc(sizeof(char*)*(s.nbr_attributs-1)); //-2 car on enleve l'etiquette
    if (s.liste_attributs_dispo == NULL) {
        fprintf(stderr, "Memory allocation failed for liste_attributs_dispo.\n");
        exit(1);
    }
    for(i=0;i<s.nbr_attributs-1;i++){
        s.liste_attributs_dispo[i] = strdup(s.tableau[0][i]);
        printf("%s\n",s.liste_attributs_dispo[i]);

    }
    s.nbr_valeur_max_attribut=cherche_valeur_max(s);
    s.ordre_exemple=malloc(sizeof(int)*s.nbr_exemples);
    for(i=0;i<s.nbr_exemples;i++){
        s.ordre_exemple[i]=i+1;
        printf("taille actuel ordre_exemple : %d et valeur : %d\n",i,i+1);

    }
    printf("taille max ordre_exemple : %d\n",i);
 



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
    printf("nbr etiquette : %d\n",s.nbr_etiquette); 
    printf("nbr valeur_max_attribut : %d\n",s.nbr_valeur_max_attribut); 

}

void afficher_etiquette(stockage s){
    printf("nbr_etiquette %d\n",s.nbr_etiquette);
    for(int i=0;i<s.nbr_etiquette;i++){
        printf("etiquette i:%d,%s\n",i,s.liste_etiquette[i]);
    }
}

void free_stockage(stockage s) {
    // Libérer la mémoire allouée pour chaque attribut de chaque exemple
    for (int i = 0; i < s.nbr_exemples + 1; i++) {
        for (int j = 0; j < s.nbr_attributs + 1; j++) {
            free(s.tableau[i][j]);
        }
        free(s.tableau[i]);
    }

    // Libérer la mémoire pour le tableau de données
    free(s.tableau);

    // Libérer la mémoire pour chaque attribut disponible
    for (int i = 0; i < s.nbr_attributs -1; i++) {
        free(s.liste_attributs_dispo[i]);
    }

    // Libérer la mémoire pour la liste des attributs disponibles
    free(s.liste_attributs_dispo);

    // Libérer la mémoire pour chaque étiquette
    for (int i = 0; i < s.nbr_etiquette; i++) {
        free(s.liste_etiquette[i]);
    }

    // Libérer la mémoire allouée pour la liste des étiquettes
    free(s.liste_etiquette);
    free(s.ordre_exemple);
}
decoupage init_decoupe(int ** tab_de_trie,int debut,int fin,stockage s){
    int i,curr=debut,pos=1,taille=0;
    decoupage new_decoupe;
    while(taille<s.nbr_valeur_max_attribut && tab_de_trie[taille][0]!=0 ){
        taille++;
    }
    new_decoupe.indice_decoupe=malloc(sizeof(int)*(taille+1));
    new_decoupe.indice_decoupe[0]=debut+1;
    for(i=0;i<taille;i++){
        curr+=tab_de_trie[i][0];
         new_decoupe.indice_decoupe[pos]=curr;
         pos++;
    }
    new_decoupe.nbr_decoupe=taille;
    return new_decoupe;

}
void free_decoupe(decoupage decoupe){
    free(decoupe.indice_decoupe);

}


int ** init_tab(int lignes,int colonnes){
    int ** tableau;
    //printf("lignes %d",lignes);
    // Allocation de mémoire pour les pointeurs de lignes
    tableau = (int **)malloc(lignes * sizeof(int *));
    if (tableau == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allocation de mémoire pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        tableau[i] = (int *)malloc((colonnes+1) * sizeof(int)); //on ajoute une case pour stocker la taille de la ligne en son debut
        if (tableau[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
        tableau[i][0]=0;
    }
    /*
    for(int i=0;i<lignes;i++){
        for(int j=0;j<tableau[i][0]+1;j++){
            printf("tab i  j:%d %d %d\n",tableau[i][j],i,j);

        }
    }*/
    return tableau;
}
int** reset_tab(int lignes,int colonnes, int ** tab){
    for(int i=0;i<lignes;i++){
        tab[i][0]=0;
    }
    return tab;
}

int * cherche_valeur(stockage s,int attributchoisie,int debut,int fin){
    int * dejaVu=malloc(sizeof(int)*(s.nbr_valeur_max_attribut+1));
    int taille=1;
    //printf("debut %d\n",debut);
    dejaVu[0]=taille; //on stocke la taille dans la premiere case de dejaVu

    for(int i=debut;i<fin;i++){
            //printf("i %d ordre_exemple %d\n",i,s.ordre_exemple[i]);
            if(taille==1 || notInList(attributchoisie,s.ordre_exemple[i],s,dejaVu,taille)==1){
                dejaVu[taille]=s.ordre_exemple[i];
                //printf("dejaVu %d taille %d\n",dejaVu[taille],taille);
                taille++;

            }
    }
    dejaVu[0]=taille; //on stocke la taille dans la premiere case de dejaVu

    return dejaVu;
}

void afficher_trie(stockage s){
    for(int i=0;i<s.nbr_exemples;i++){
        printf("ligne %d :",i+1);
        for(int j=0;j<s.nbr_attributs;j++){
                printf("%s ",s.tableau[s.ordre_exemple[i]][j]);
            }
        printf("\n");
    }
}


void afficher_decouper(decoupage decoupe){
    printf("nbr decoupe : %d\n",decoupe.nbr_decoupe);
    for(int i=0;i<decoupe.nbr_decoupe;i++){
        printf("indice decoupe : %d\n",decoupe.indice_decoupe[i]);
    }
}


decoupage Trie_Stockage_attribut(stockage *s, int attributchoisie,int debut, int fin){
    //Trie la structure stockage pour separer les exemples selon le critère indiqué de la case debut à la case fin.
    //ENleve egalement l'attribut des attributs disponible.
    int i,j,k;
    decoupage decoupe;
    static int initialized = 0; // Variable pour vérifier si les tableaux ont étés initialisée

    static int ** trie;
    int *  valeur_possible=cherche_valeur(*s,attributchoisie,debut,fin);
    if(initialized==0){
        trie=init_tab(s->nbr_valeur_max_attribut,s->nbr_exemples);
    }
    else{
        trie=reset_tab(s->nbr_valeur_max_attribut,s->nbr_exemples,trie);
    }
    printf("taille valeur_possible=%d\n",valeur_possible[0]);
    for(int i=1;i<valeur_possible[0];i++){
        printf("valeur i=%d cad %s\n",valeur_possible[i],s->tableau[valeur_possible[i]][attributchoisie]);
    }
    /*
    for(i=1;i<s->nbr_exemples;i++){
        printf("%s\n",s->tableau[i][attributchoisie]);
    }
    */
    for(i=debut;i<fin;i++){
        for(j=1;j<valeur_possible[0];j++){
                //printf("i :%d ,ordre exemple:%d valeur_possible : %d %s %s\n",i,s->ordre_exemple[i],valeur_possible[j],s->tableau[valeur_possible[j]][attributchoisie],s->tableau[s->ordre_exemple[i]][attributchoisie]);

            if(strcmp(s->tableau[valeur_possible[j]][attributchoisie],s->tableau[s->ordre_exemple[i]][attributchoisie])==0){
                trie[j-1][0]++;  
                trie[j-1][trie[j-1][0]]=s->ordre_exemple[i];
                //printf("on ajoute\n");
                //printf("trie %d ligne j :%d taille_trie %d\n",trie[j][trie[j][0]],j,trie[j][0]);
            }
        }
    }
    k=debut;
    for(i=0;i<valeur_possible[0]-1;i++){
        //printf("taille %d pour i %d\n",trie[i][0],i);
        for(j=1;j<trie[i][0]+1;j++){
            //printf("ligne %d pour i %d et j %d\n",trie[i][j],i,j);

            s->ordre_exemple[k]=trie[i][j];
            k++;

        }
    }
    
    for(i=0;i<s->nbr_valeur_max_attribut;i++){
        for(j=0;j<trie[i][0];j++){
            printf("trie i  j:%d %d %d\n",trie[i][j],i,j);

        }
    }

    decoupe=init_decoupe(trie,debut,fin,*s);
    free(valeur_possible);
    return decoupe;

}





