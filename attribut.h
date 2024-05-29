#ifndef attribut_H
#define attribut_H
typedef struct attribut{
    int nb_colonnes;
    int *nb_elements_par_colonne;
    int ** compteur;
    char *** pointeur;
    int nbr_etiquette;
} attribut;


static attribut initialise_attribut(stockage s);
void affiche_attribut(attribut attr);
attribut renitialise_attribut(attribut attr);
attribut rempli_attribut(stockage s,int index_attribut, int debut, int fin);
void liberer_attribut(attribut *attr, int nb_exemples)
#endif