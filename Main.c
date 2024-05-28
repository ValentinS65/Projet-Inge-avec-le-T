#include <stdio.h>
#include <time.h>
#include"stockage.h"
#include"attribut.h"
#include"entropie.h"
#include"arbre_de_decision.h"
int main(){
    stockage e=extraction_fichier("test2.txt");
    //attribut a=Valeur_Attribut(e,0,e.nbr_etiquette);
    printf("TAILLE FICHIER %d",e.nbr_exemples);
    printf("test 1\n");
    afficher_tableau(e);
    srand(time(NULL));
/*
    noeud *arbre = ID_3(e, 0, e.nbr_exemples, 0);
    char *exemple[] = {"rouge", "rond", "grand","10","1","25","10"}; // Remplissez avec les valeurs des attributs de l'exemple
   
  

    char *resultat = predire(arbre, exemple,e);
    printf("L'étiquette prédite est : %s\n", resultat);
*/
    //afficher_arbre(arbre,0);
    //printf("test 2\n");
    
    //afficher_etiquette(e);
    
    printf("test 3\n\n");
    afficher_decouper(Trie_Stockage_attribut(&e,0,0,e.nbr_exemples-1));
    afficher_trie(e);

    printf("test 4\n\n");

    afficher_decouper(Trie_Stockage_attribut(&e,1,4,6));
    afficher_trie(e);
    
    printf(" test 5\n");
    afficher_decouper(Trie_Stockage_attribut(&e,1,6,9));
    afficher_trie(e);
    printf(" test 6\n");
    afficher_decouper(Trie_Stockage_attribut(&e,1,10,e.nbr_exemples-1));
    afficher_trie(e);

    printf("test 5\n\n");

    afficher_decouper(Trie_Stockage_attribut(&e,3,3,5));
    afficher_trie(e);
    



    //affiche_attribut(a,e);
    //printf("L'attribut choisi : %s",e.liste_attributs_dispo[Choix_attribut_noeud(a,e)]);
    //float test=gain(a,e,0);
   // printf("mon test : %f\n",test);
    //float test2=entropie(a.nbr_apparition[0][0],e.nbr_etiquette);
    //printf("mont test2 : %f\n",test2);
    //free_attribut(a,e);
   // attribut attr= rempli_attribut(e,0,1,e.nbr_exemples+1);
    //attribut attr2=rempli_attribut(e,1,1,e.nbr_exemples+1);

    
    //int test1=choix_attribut(e,1,e.nbr_exemples+1);
    //double test2=gain_sans_le_set(attr);
    //printf("Mon test1 sur 'entropie : %d \n",test1);
    //printf("indice du meilleur attribut : %d",choix_attribut(e,1,e.nbr_exemples));
    free_stockage(e);
    
}