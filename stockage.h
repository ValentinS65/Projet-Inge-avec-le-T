#ifndef stockage_H
#define stockage_H
typedef struct stockage{
    char *** tableau;
    char ** liste_attributs_dispo;
    char ** liste_etiquette;
    int nbr_attributs;
    int nbr_exemples;
    int nbr_etiquette;
    int nbr_valeur_max_attribut;
    int * ordre_exemple;
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
void afficher_trie(stockage s);
void Trie_Stockage_attribut(stockage *s, int attributchoisie,int debut, int fin);
#endif 