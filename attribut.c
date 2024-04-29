#include "arbre_de_decision_v2.h"

int main(){
    stockage e=extraction_fichier("test.txt");
    //attribut a=Valeur_Attribut(e,0,e.nbr_etiquette);
    afficher_tableau(e);
    afficher_etiquette(e);
    //affiche_attribut(a,e);
    //printf("L'attribut choisi : %s",e.liste_attributs_dispo[Choix_attribut_noeud(a,e)]);
    //float test=gain(a,e,0);
   // printf("mon test : %f\n",test);
    //float test2=entropie(a.nbr_apparition[0][0],e.nbr_etiquette);
    //printf("mont test2 : %f\n",test2);
    //free_attribut(a,e);
    free_stockage(e);
    
}