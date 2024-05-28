#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stockage.h"
#include "attribut.h"
#include "entropie.h"
#include "arbre_de_decision.h"
#define nbr_exemples_minimal 1
#define MAX_DEPTH 2

noeud* ID_3 (stockage s,int debut, int fin,int profondeur){
    printf("INITIALISE UN NOEUD \n");
    noeud *actuel = (noeud*)malloc(sizeof(noeud));
    actuel->profondeur = profondeur;
    actuel->etiquette_counts = NULL;
    actuel->total_etiquettes = 0;
    actuel->classe=NULL;
    int flag=1;
    for (int i=debut; i<fin; i++){
        //printf("%s %s",s.tableau[i][s.nbr_attributs-1],s.tableau[i+1][s.nbr_attributs-1]);
        if (strcmp(s.tableau[i][s.nbr_attributs-1],s.tableau[i+1][s.nbr_attributs-1])!=0){
            flag=0;
            printf("PAS UNE FEUILLE\n");
            break;
        }
    }

     if (flag) {
        printf("CREER UNE FEUILLE\n");
        // Créer un nœud feuille
        actuel->attribut = NULL;
        actuel->nb_sous_arbres = 0;
        actuel->indice_sous_arbres = (int*)malloc(2* sizeof(int));
        actuel->indice_sous_arbres[0] = debut;
        actuel->indice_sous_arbres[1] = fin;
       
        actuel->profondeur = profondeur;
        actuel->sous_arbres = NULL;
        actuel->classe = s.tableau[debut][s.nbr_attributs-1];
        return actuel;
    }
    

    if(profondeur>MAX_DEPTH || fin-debut<nbr_exemples_minimal){
        printf("ON DEPASSE LA PROFONDEUR OU LE NOMBRE DELEMENT");
        EtiquetteCount *etiquette_counts = malloc((fin - debut) * sizeof(EtiquetteCount));
        int unique_count = 0;

        for (int i = debut; i < fin; i++) {
            char *etiquette = s.tableau[i][s.nbr_attributs-1];
            int found = 0;
            for (int j = 0; j < unique_count; j++) {
                if (strcmp(etiquette_counts[j].etiquette, etiquette) == 0) {
                    etiquette_counts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                etiquette_counts[unique_count].etiquette = etiquette;
                etiquette_counts[unique_count].count = 1;
                unique_count++;
            }
        }

        actuel->etiquette_counts = etiquette_counts;
        actuel->total_etiquettes = unique_count;

        
        actuel->attribut = NULL;
        actuel->nb_sous_arbres = 0;
        actuel->indice_sous_arbres = (int*)malloc(2 * sizeof(int));
        actuel->indice_sous_arbres[0] = debut;
        actuel->indice_sous_arbres[1] = fin;

       

        return actuel;
    }
    

    printf("CREATION CLASSIQUE");
    //Choix du meilleur attribut pour l'ensemble
    int indice=choix_attribut(s,debut,fin);
    printf("Indice : %d",indice);

    //Création du noeud intermediaire
   
    actuel->attribut = s.tableau[0][indice];
    decoupage trie=Trie_Stockage_attribut(&s, indice, debut, fin);
    afficher_trie(s);
    afficher_decouper(trie);
    actuel->indice_sous_arbres = trie.indice_decoupe;
    actuel->nb_sous_arbres =trie.nbr_decoupe;
    actuel->sous_arbres = (noeud**)malloc(actuel->nb_sous_arbres * sizeof(noeud*));
    
     for (int i = 0; i < actuel->nb_sous_arbres; i++) {
        int sub_debut = actuel->indice_sous_arbres[i];
        int sub_fin = (i == actuel->nb_sous_arbres - 1) ? fin : actuel->indice_sous_arbres[i + 1];
        actuel->sous_arbres[i] = ID_3(s, sub_debut, sub_fin, profondeur + 1);
    }

    return actuel;


}


char* tirer_au_hasard(EtiquetteCount *etiquette_counts, int unique_count) {
    int total = 0;
    for (int i = 0; i < unique_count; i++) {
        total += etiquette_counts[i].count;
    }

    int r = rand() % total;
    int sum = 0;
    for (int i = 0; i < unique_count; i++) {
        sum += etiquette_counts[i].count;
        if (r < sum) {
            return etiquette_counts[i].etiquette;
        }
    }

    return etiquette_counts[unique_count - 1].etiquette;
}



char* predire(noeud * arbre, char **exemple,stockage s) {
    if (arbre == NULL) {
        return NULL;
    }

    // Si c'est une feuille, retourner l'étiquette de classe
    if (arbre->nb_sous_arbres == 0) {
       if (arbre->classe != NULL) {
            return arbre->classe;
        } else {
            return tirer_au_hasard(arbre->etiquette_counts, arbre->total_etiquettes);
        }
    }

    // Trouver l'indice de l'attribut correspondant dans l'exemple
    int indice_attribut = -1;
    for (int i = 0; i < s.nbr_attributs; i++) {
        if (strcmp(s.liste_attributs_dispo[i], arbre->attribut) == 0) {
            indice_attribut = i;
            break;
        }
    }

    // Si l'attribut n'est pas trouvé, retourner NULL (ou une valeur par défaut)
    if (indice_attribut == -1) {
        return NULL;
    }

    // Parcourir les sous-arbres
    for (int i = 0; i < arbre->nb_sous_arbres; i++) {
        int sub_debut = arbre->indice_sous_arbres[i];
        int sub_fin = (i == arbre->nb_sous_arbres - 1) ? sub_debut : arbre->indice_sous_arbres[i + 1];
        if (strcmp(exemple[indice_attribut], s.tableau[sub_debut][indice_attribut]) == 0) {
            return predire(arbre->sous_arbres[i], exemple, s);
        }
    }

    return NULL; // Si aucune correspondance n'est trouvée
}

void afficher_arbre(noeud *arbre, int niveau) {
    if (arbre == NULL) {
        return;
    }

    // Indentation pour montrer le niveau de profondeur
    for (int i = 0; i < niveau; i++) {
        printf("    ");
    }

    // Afficher l'attribut ou l'étiquette de classe
    if (arbre->nb_sous_arbres == 0) {
        printf("Feuille: %s\n", arbre->classe);
    } else {
        printf("Attribut: %s\n", arbre->attribut);
    }

    // Afficher récursivement les sous-arbres
    for (int i = 0; i < arbre->nb_sous_arbres; i++) {
        afficher_arbre(arbre->sous_arbres[i], niveau + 1);
    }
}
