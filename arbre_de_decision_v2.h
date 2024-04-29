#ifndef arbre_de_decision_H
#define arbre_de_decision_H
typedef struct stockage{
    char *** tableau;
    char ** liste_attributs_dispo;
    char ** liste_etiquette;
    int nbr_attributs;
    int nbr_exemples;
    int nbr_etiquette;
}stockage;
int inList(char ** l, char * mot,int taille);
char ** cherche_etiquette(stockage *s);
stockage extraction_fichier(char * fichier);
void afficher_tableau(stockage s);

void afficher_etiquette(stockage s);
void free_stockage(stockage s);

#endif 