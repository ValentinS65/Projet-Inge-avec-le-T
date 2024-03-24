#include <stdio.h>
#include <stdlib.h>

//Structure pour attribut du dico: Contient une cle et une valeur
typedef struct attribut{
    char * cle;
    char * valeur;
}attribut;

/*Structure du dico  : Contient -> un tableau d'attribut
                                -> une taille
                                -> la position dans le tableau(sert pour le stockage)

*/
typedef struct dico{
    attribut * dict;
    int taille;
    int pos;
}dico;

//Fonction d'initialisation du dictionnaire
dico createur_dico(int nb_attributs){
    dico dictionnaire;
    dictionnaire.taille=nb_attributs;
    dictionnaire.pos=0;
    dictionnaire.dict=malloc(sizeof(attribut)*dictionnaire.taille); 
    return dictionnaire;
}

//Fonction d'ajout dans le "dictionnaire"
void ajoute_dico(char * key,char * value,dico dictionnaire){
    if(dictionnaire.pos!=dictionnaire.taille){ //On vérifie qu'on ne depasse pas le nombre max d'attribut
        dictionnaire.dict[dictionnaire.pos].cle=key;
        dictionnaire.dict[dictionnaire.pos].valeur=value;
        dictionnaire.pos++;
    }
}

//Fonction de recherche dans le dictionnaire
char * chercher_cle(char * key,dico dictionnaire){
    int postemp=0;
    while(dictionnaire.dict[dictionnaire.pos].cle!= key && postemp!=dictionnaire.taille){
        postemp++;
    }
    if(postemp!=dictionnaire.taille){
        return dictionnaire.dict[dictionnaire.pos].valeur;
    }
    else{
        return NULL;
    }
}
