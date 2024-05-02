

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre_de_decision_v2.h"
#include "attribut.h"


//Initialiseur de la structure attribut
attribut initialise_attribut(stockage s){
    attribut a;
    char *** pointeur;
    int ** compteur;
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
    for (int i=0;i<s.nbr_exemples+1;i++){
        pointeur[i]=malloc(sizeof(char**)*(s.nbr_exemples+1));
        if (pointeur[i] == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        compteur[i]=malloc(sizeof(int)*(s.nbr_exemples+1));
        if (compteur[i] == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for (int j = 0; j < s.nbr_exemples + 1; j++) {
            pointeur[i][j] = NULL;
        }
    }
    a.index=0;
    a.pointeur=pointeur;
    a.compteur=compteur;
    return a;
}


//Utilisé pour le test uniquement
void affiche_attribut(attribut attr){
    int i=0;
    while(attr.pointeur[i][0]!=NULL){ 
        
        int j=0;
        while(attr.pointeur[i][j]!=NULL){
            if (j==0){
                printf("Attribut: %s nombre : %d\n",attr.pointeur[i][j],attr.compteur[i][j]);
            }
            else{
                printf("valeur : %s nombre : %d\n",attr.pointeur[i][j],attr.compteur[i][j]);
            }
            j++;
        }
        i++;
    }
}

attribut rempli_attribut(stockage s,int index_attribut, int debut, int fin){
    static attribut attr=initialise_attribut(s);
    for (int e=debut;e<fin;e++){ //PArcours tous les exemples
        int i=0;
        int exit1=0; //exit de la première boucle
        int exit2=0; //exit de la deuxième boucle
        int j=1;
        while(exit1==0 && attr.pointeur[i][0]!=NULL){
            if (strcmp(s.tableau[e][index_attribut],attr.pointeur[i][0])==0){
                attr.compteur[i][0]++;
                exit1=1;
                printf("Sa passe ici 2 : %s\n",attr.pointeur[i][0]);
            }
            else{
                i++;
            }
            
        }
        if (exit1==0){
            attr.pointeur[i][0]=s.tableau[e][index_attribut];
            attr.compteur[i][0]=1;
            printf("Sa passe ici 1 : %s\n",attr.pointeur[i][0]);
        }
        
        while (exit2==0 && attr.pointeur[i][j]!=NULL){
            if (strcmp(s.tableau[e][s.nbr_attributs-1],attr.pointeur[i][j])==0){
                attr.compteur[i][j]++;
                exit2=1;
                printf("Sa passe ici 3 :%s \n",attr.pointeur[i][j]);
            }
            else{
                j++;
            }
        }
    
        if (exit2==0){
            attr.pointeur[i][j]=s.tableau[e][s.nbr_attributs-1];
            attr.compteur[i][j]=1;
            printf("Sa passe ici 4 %s \n ",attr.pointeur[i][j]);
        }
        
        

    }
    return attr;
}

attribut vide_attribut(attribut a,stockage s){
    for (int i=0;i<s.nbr_exemples;i++){
        for (int j=0;j<s.nbr_exemples;j++){
            a.pointeur[i][j]=NULL;
        }
    }
}

int main(){
    stockage e=extraction_fichier("test.txt");
    //attribut a=Valeur_Attribut(e,0,e.nbr_etiquette);
    afficher_tableau(e);
    afficher_etiquette(e);
    //affiche_attribut(a,e);
    //printf("L'attribut choisi : %s",e.liste_attributs_dispo[Choix_attribut_noeud(a,e)]);
    //float test=gain(a,e,0);
   // printf("mon test : %f\n",test);
    //float test2=entropie(a.nbr_apparition[0][0],e.nbr_etiquette);
    //printf("mont test2 : %f\n",test2);
    //free_attribut(a,e);
    attribut attr=initialise_attribut(e);
    attr=rempli_attribut(attr,e,0,1,e.nbr_exemples+1);
    affiche_attribut(attr);

    free_stockage(e);
    
}