#include <stdio.h>

#include"arbre_de_decision_v2.h"
#include"attribut.h"
#include"entropie.h"
int main(){
    stockage e=extraction_fichier("test.txt");
    //attribut a=Valeur_Attribut(e,0,e.nbr_etiquette);
    printf("test 1\n");
    afficher_tableau(e);
    //printf("test 2\n");

    //afficher_etiquette(e);
    printf("test 3\n");
    Trie_Stockage_attribut(&e,4,1,e.nbr_exemples);
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
    //printf("indice du meilleur attribut : %d",choix_attribut(e,1,e.nbr_exemples+1));
    free_stockage(e);
    
}