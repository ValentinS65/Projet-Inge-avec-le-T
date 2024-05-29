

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stockage.h"
#include "attribut.h"


//Initialiseur de la structure attribut
static attribut initialise_attribut(stockage s){
    attribut a;
    char *** pointeur;
    int ** compteur;
    int * nb_elements_par_colonne;
    //Initialisation de nos tableaux)
    compteur=malloc(sizeof(int *)*(s.nbr_exemples+1));
    if (compteur == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    pointeur=malloc(sizeof(char***)*(s.nbr_exemples+1));
    if (pointeur == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    nb_elements_par_colonne = malloc(sizeof(int) * (s.nbr_exemples + 1));
    if (nb_elements_par_colonne == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for (int i=0;i<s.nbr_exemples+1;i++){
        pointeur[i]=malloc(sizeof(char**)*(s.nbr_etiquette+1));
        if (pointeur[i] == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        compteur[i]=malloc(sizeof(int)*(s.nbr_etiquette+1));
        if (compteur[i] == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        nb_elements_par_colonne[i] = 0;
        for (int j = 0; j < s.nbr_etiquette + 1; j++) {
            pointeur[i][j] = NULL;
        }
    }
    a.pointeur=pointeur;
    a.compteur=compteur;
    a.nb_elements_par_colonne=nb_elements_par_colonne;
    a.nb_colonnes=0;
    a.nbr_etiquette=s.nbr_etiquette;
    return a;
}


//Utilisé pour le test uniquement
void affiche_attribut(attribut attr){
    for (int i=0;i<attr.nb_colonnes;i++){
        for(int j=0;j<=attr.nb_elements_par_colonne[i];j++){
            if (j==0){
                printf("Attribut: %s nombre : %d\n",attr.pointeur[i][j],attr.compteur[i][j]);
            }
            else{
                printf("valeur : %s nombre : %d\n",attr.pointeur[i][j],attr.compteur[i][j]);
            }
        }
    }

}
attribut renitialise_attribut(attribut attr){
    for (int i=0;i<attr.nb_colonnes;i++){
        for (int j=0;j<attr.nb_elements_par_colonne[i]+1;j++){
            attr.compteur[i][j]=0;
        }
        attr.nb_elements_par_colonne[i]=0;
        
    }
    attr.nb_colonnes=0;
    return attr;
}



attribut rempli_attribut(stockage s,int index_attribut, int debut, int fin){
    static attribut attr; // Déclaration de la variable statique
    static int initialized = 0; // Variable pour vérifier si attr a été initialisée

    if (!initialized) {
        attr = initialise_attribut(s); // Initialisation de attr uniquement lors du premier appel
        initialized = 1;
    }
    else{
        attr=renitialise_attribut(attr);
    }
    for (int e=debut;e<fin;e++){ //PArcours tous les exemples
        int i=0;
        int exit1=0; //exit de la première boucle
        int exit2=0; //exit de la deuxième boucle
        int j=1;
        while(exit1==0 && i<attr.nb_colonnes){
            if (strcmp(s.tableau[s.ordre_exemple[e]][index_attribut],attr.pointeur[i][0])==0){
                attr.compteur[i][0]++;
                exit1=1;
                //printf("Sa passe ici 2 : %s\n",attr.pointeur[i][0]);
            }
            else{
                i++;
            }
            
        }
        if (exit1==0){
            attr.pointeur[i][0]=s.tableau[s.ordre_exemple[e]][index_attribut];
            attr.compteur[i][0]=1;
            attr.nb_colonnes++;
            //printf("Sa passe ici 1 : %s\n",attr.pointeur[i][0]);
        }
        
        while (exit2==0 && j<attr.nb_elements_par_colonne[i]+1){
            if (strcmp(s.tableau[s.ordre_exemple[e]][s.nbr_attributs-1],attr.pointeur[i][j])==0){
                attr.compteur[i][j]++;
                exit2=1;
                //printf("Sa passe ici 3 :%s \n",attr.pointeur[i][j]);
            }
            else{
                j++;
            }
        }
    
        if (exit2==0){
            attr.pointeur[i][j]=s.tableau[s.ordre_exemple[e]][s.nbr_attributs-1];
            attr.compteur[i][j]=1;
            attr.nb_elements_par_colonne[i]++;
            //printf("Sa passe ici 4 %s \n ",attr.pointeur[i][j]);
        }
        
        

    }
    
    //affiche_attribut(attr);
    return attr;
}

void liberer_attribut(attribut *attr, int nb_exemples) {
    // Libérer chaque tableau de pointeur et compteur
    for (int i = 0; i < nb_exemples + 1; i++) {
        free(attr->pointeur[i]); // Libérer le tableau de pointeur
        free(attr->compteur[i]); // Libérer le tableau de compteur
    }

    // Libérer les tableaux principaux
    free(attr->pointeur); // Libérer le tableau des pointeurs
    free(attr->compteur); // Libérer le tableau des compteurs
    free(attr->nb_elements_par_colonne); // Libérer le tableau du nombre d'éléments par colonne
}



