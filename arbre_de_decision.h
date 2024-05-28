#ifndef Arbre_H
#define Arbre_H
typedef struct EtiquetteCount {
    char *etiquette; //Nom de l'etiquette
    int count; //Nombre d'apparition 
} EtiquetteCount;
typedef struct noeud{
    char * attribut; // Attribut qui a coupé cette section
    int  nb_sous_arbres; //Nombre de fils du noeud
    int * indice_sous_arbres;// indice des exemples des fils
    struct noeud ** sous_arbres;// Tableau des fils
    int profondeur;//Profondeur du noeud
    char * classe;// Etiquette du noeud si elle existe
    EtiquetteCount *etiquette_counts; // nombre et nom des etiquettes du sous-arbres,
    // utiliser quand la profondeur est supérieur au max
    int total_etiquettes; //Nombre d'étiquette differentes de la feuille 
} noeud;

noeud* ID_3 (stockage s,int debut, int fin,int profondeur);
char* tirer_au_hasard(EtiquetteCount *etiquette_counts, int unique_count);
char* predire(noeud * arbre, char **exemple,stockage s);
void afficher_arbre(noeud *arbre, int niveau);

#endif