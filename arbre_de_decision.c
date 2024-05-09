#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stockage.h"
#include "attribut.h"
#include "entropie.h"
#include "arbre_de_decision.h"
#define nbr_exemples_minimal 4
#define MAX_DEPTH 10

noeud ID_3 (stockage s,int debut, int fin,int profondeur){
    noeud noeud;
    if (debut-fin<nbr_exemples_minimal){
        return null;
    }

    if(profondeur>MAX_DEPTH){
        return null;
    }

    int flag=1;
    for (int i=debut; i<fin; i++){
        if (strcmp(s[i][s.nbr_attributs],s[i+1][s.nbr_attributs])!=0){
            flag=0;
        }
    }

    if (flag==0){
        noeud.attribut=null;
        noeud.nb_sous_arbres=0;
        int * tab=malloc(3*sizeof(int));
        tab[0]=0;
        tab[1]=debut;
        tab[2]=fin;
        noeud.indice_sous_arbres= tab;
        noeud.profondeur=profondeur;
        return noeud;
    }

    int indice=choix_attribut(s,debut,fin);
    noeud.attribut=s[0][indice];
    noeud.indice_sous_arbres=Trie_Stockage_attribut(s,indice,debut,fin);
    noeud.nb_sous_arbres=0;//Pour l'instant je ne connais pas l'implémentation de valentin
    for (int i=0;i<noeud.nb_sous_arbres;i++){
        //JE ne sais pas comment mettre en oeuvre ma recurssion sur tout les sous ensembles
        int sub_debut = noeud.indice_sous_arbres[i]; // Début du sous-ensemble
        int sub_fin = (i == noeud.nb_sous_arbres - 1) ? fin : noeud.indice_sous_arbres[i + 1]; // Fin du sous-ensemble
        noeud.sous_arbres[i] = ID_3(s, sub_debut, sub_fin, profondeur + 1);
    }   
    //Je ne conserve qu'un seul noeud = problème




}