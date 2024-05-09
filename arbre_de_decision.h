#ifndef Arbre_H
#define Arbre_H
typedef struct{
    char * attribut;
    int  nb_sous_arbres;
    int * indice_sous_arbres;
    int profondeur;
} noeud;

#endif