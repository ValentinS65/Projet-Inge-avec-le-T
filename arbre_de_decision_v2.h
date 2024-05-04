#ifndef arbre_de_decision_H
#define arbre_de_decision_H
typedef struct stockage{
    char *** tableau;
    char ** liste_attributs_dispo;
    char ** liste_etiquette;
    int nbr_attributs;
    int nbr_exemples;
    int nbr_etiquette;
    int nbr_valeur_max_attribut;
}stockage;
int inList(char ** l, char * mot,int taille);
char ** cherche_etiquette(stockage *s);
int notInList(int i,int j,stockage s,int * dejaVu, int taille);
int cherche_valeur_max(stockage s);
stockage extraction_fichier(char * fichier);
void afficher_tableau(stockage s);

void afficher_etiquette(stockage s);
void free_stockage(stockage s);
int ** init_tab(int lignes,int colonnes);
void Trie_Stockage_attribut(stockage *s, int attributchoisie,int debut, int fin);
#endif 