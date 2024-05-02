#ifndef attribut_H
#define attribut_H
typedef struct{
    int nb_colonnes;
    int *nb_elements_par_colonne;
    int ** compteur;
    char *** pointeur;
} attribut;

#endif