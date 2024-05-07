#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arbre_de_decision_v2.h"
#include "attribut.h"

double entropie(attribut attr, int index){
    double entropie=0.0;
    double log_base=log(attr.nbr_etiquette);
    printf("En base : %d",attr.nbr_etiquette);
    for(int j=1;j<attr.nb_elements_par_colonne[index]+1;j++){
        double prob = (double )  attr.compteur[index][j] / attr.compteur[index][0];
        printf("Prob num %d : %f",j,prob);
        if (prob > 0.0) {
            entropie -= prob *( log(prob) / log_base);
        }
    }
    return entropie;
}

double gain_sans_le_set(attribut attr){
    double entropie_current=0.0;
    float total=0.0;
    for (int i=0;i<attr.nb_colonnes;i++){
        total+=attr.compteur[i][0];
    }
    printf("Le total : %f\n",total);
    for (int i=0;i<attr.nb_colonnes;i++){
        double prob = (double) (attr.compteur[i][0] / total);
        printf("La proba devant l'entropie %f\n",prob);
        if (prob > 0.0) {
            double entropietemp=entropie(attr, i);
            entropie_current -= prob * entropietemp;
            printf("Entropie : %f ",entropietemp);
            printf("Entropie current : %f\n",entropie_current);
        }
    }
    return entropie_current;
}

double entropie_set(stockage s,int debut, int fin){
    attribut attr=rempli_attribut(s,s.nbr_attributs-1,debut,fin);
    double entropie_current=0.0;
    float total=fin-debut;
    
     for(int i=0;i<attr.nb_colonnes;i++){
        if (attr.compteur[i][0] != 0) {
            double prob =(double) attr.compteur[i][0]/total;
            entropie_current-=(prob)*log(prob)/log(attr.nbr_etiquette);
        }
    }
    return entropie_current;
}


int choix_attribut(stockage s, int debut, int fin){
    double entropie_du_set = entropie_set(s, debut, fin);
    double gain_max = -1.0; // Initialisation de gain_max avec l'entropie du set
    int indice_max = -1;
    for (int i = 0; i < s.nbr_attributs-1; i++){
        attribut attr = rempli_attribut(s, i, debut, fin);
        double gain = gain_sans_le_set(attr); // Calcul du gain pour l'attribut courant
        
        // Ajout du gain pour l'attribut courant à gain_max
        gain += entropie_du_set;
        printf("Gain du set n° %d : %f",i,gain);
        // Mise à jour de gain_max et indice_max si gain courant est supérieur à gain_max
        if (gain > gain_max){
            gain_max = gain;
            indice_max = i;
        }
    }
    return indice_max;
}