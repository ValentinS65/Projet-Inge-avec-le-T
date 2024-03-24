#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "gestion_fichier.h"


//Structure Exemple contient une etiquette(classe) et un dictionnaire de valeur pour chaque attribut
typedef struct Exemple{
    char * etiquette;
    dico attribut;
}Exemple;

//Structure Ensemble contenant la liste des attributs et la liste des exemples
typedef struct Ensemble{
    char ** liste_attributs;
    Exemple * liste_exemple;
}Ensemble;

//Structure Noeud contient la liste des enfants (sous forme de dico) et l'attribut testé sur le noeud
typedef struct Noeud{
    dico enfants;
    char attribut_testé;
}Noeud;

//Structure Arbre contient un ensemble ainsi que l'arbre de décision
typedef struct Arbre_ID3{
    Ensemble ensemble;
    Noeud  * arbre;
}Arbre_ID3;


//Fonction servant a initialiser un Exemple
Exemple constructeur_Exemple(int nbr_attributs,char ** nom_attributs,char ** valeur_attributs,char * etiquette){
    Exemple exemple;
    exemple.etiquette=etiquette; //Affectation de l'etiquette
    exemple.attribut=createur_dico(nbr_attributs); //Initialisation du dico 
    //On rempli le dico avec notre exemple
    for(int i=0;i<nbr_attributs;i++){
        ajoute_dico(nom_attributs[i],valeur_attributs[i],exemple.attribut);
    }
    return exemple;
}

//Fonction servant a initialiser un Ensemble
Ensemble constructeur_Ensemble(char * nom_fichier){
    Ensemble ensemble;
    char ligne[2000]; //chaine de caractere servant a contenir les lignes du fichier
    char * etiquette;
    char ** liste_exemple_tmp;  
    int nbr_mot=1,nbr_mot_ligne=1,i=0,j=0,nbr_lignes=1; /*ON initialise les 2 compteurs : nbr_mot -> compte le nombre d'attribut
                                                                         nbr_mot_ligne vérifie la présence éventuelle d'une étiquette sur une ligne exemple.*/
    FILE * fd=fopen(nom_fichier,"r"); //On ouvre le fichier en lecture
    if(fd==NULL){
        perror("Problème d'ouverture du fichier");
        exit(-1);
    }
    //On calcul le nombre de ligne du fichier
    while(EOF){
        if(fgetc(fd)=='\n'){
            nbr_lignes++;
        }
    }
    rewind(fd);
    ensemble.liste_exemple=malloc(sizeof(Exemple)*nbr_lignes); //On initialise la liste des exemples
    fgets(ligne,2000,fd); //On recupere la premiere ligne du fichier
    //On compte le nombre de mot
    while(ligne[i]!='\0'){
        if(ligne[i]==' '){
            nbr_mot++;
        }
        i++;
    }
    ensemble.liste_attributs=separateur(ligne,' '); //On separe les differends attributs dans un tableau que l'on affecte a liste_attributs (équivalent de split en python)
    printf("%s",ligne);
     //Tant que le fichier n'est pas entierement parcouru on récupère les exemples
    while(EOF){
        fgets(ligne,2000,fd); //On recupere la ligne du fichier
        //On compte le nombre de mot de la ligne
        while(ligne[i]!='\0'){
        if(ligne[i]==' '){
            nbr_mot_ligne++;
        }
        i++;
    }
        liste_exemple_tmp=separateur(ligne,' ');
        //On vérifie la présence d'une étiquette sur la ligne
        if(nbr_mot!=nbr_mot_ligne){
            etiquette=liste_exemple_tmp[nbr_mot_ligne-1];
            }
        else{
            etiquette="";
            }
        ensemble.liste_exemple[j]=constructeur_Exemple(nbr_mot,ensemble.liste_attributs,liste_exemple_tmp,etiquette); //On crée la liste d'exemple grâce a notre constructeur d'Exemple
        j++;
   
    }
    fclose(fd);
    return ensemble;
}
Arbre_ID3 constructeur_Arbre_ID3(char * chemin_fichier){
    Arbre_ID3 arbre;
    arbre.ensemble=constructeur_Ensemble(chemin_fichier);
    arbre.arbre=constructeur_Noeud();
    
}





int main(){
    constructeur_Ensemble("test.txt");
    return 0;
}
