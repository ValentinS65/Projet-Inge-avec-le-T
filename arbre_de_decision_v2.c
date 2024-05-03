#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arbre_de_decision_v2.h"


/*
typedef struct attribut{
    char *** tableau;
    int * nbr_valeur_attribut;
    int *** nbr_apparition;
    int nbr_exemples_pris_en_compte;

}attribut;

*/
int inList(char ** l, char * mot,int taille){
    for(int i=0;i<taille;i++){
        if(strcmp(mot,l[i])==0){
            return 1;
        }
    }
    return 0;
}

char ** cherche_etiquette(stockage *s){
    int pos=0;
    char ** liste_etiquette=malloc(sizeof(char*)*s->nbr_exemples);
    for(int i=1;i<s->nbr_exemples+1;i++){
        if(inList(liste_etiquette,s->tableau[i][s->nbr_attributs-1],pos)==0){ //On vérifie qu'on ajoute uniquement les etiquettes qui ne sont pas présent dans notre liste grâce à la fonction inList
            liste_etiquette[pos]=strdup(s->tableau[i][s->nbr_attributs-1]);
            //printf("etiquette: %s\n",s.tableau[i][s.nbr_attributs-1]);
            s->nbr_etiquette++;
        printf("nbr_etiquette i:%d\n",s->nbr_etiquette);

            pos++;
        }
    }
    return liste_etiquette;
}


stockage extraction_fichier(char * fichier){
    stockage s;
    int nbr_lignes=0,nbr_mots=0,i=0,j=0,pos=0;
    char c;
    char *** tableau;
    FILE * fd= fopen(fichier,"r");
    //on calcule le nombre de ligne et le nombre de mot de la premiere ligne pour malloc notre tableau
    c=fgetc(fd);
    while(c != EOF){
        if(nbr_lignes==0 && c==' '){
            nbr_mots++;
        }
        if(c=='\n'){
            nbr_lignes++;
        }
        c=fgetc(fd);
    }
    rewind(fd);

    s.nbr_attributs=nbr_mots+1;
    s.nbr_exemples=nbr_lignes;
    s.nbr_etiquette=0;
    //On revient au debut du fichier
    printf("nbr attributs : %d\n",s.nbr_attributs);
    printf("nbr exemples : %d\n",s.nbr_exemples);
    printf("nbr mots : %d\n",nbr_mots);
    printf("nbr lignes : %d\n",nbr_lignes+1);
    tableau=malloc(sizeof(char **)*(s.nbr_exemples+1)); //On initialise notre tableau de chaine de caractère
    if (tableau == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for(i=0;i<nbr_lignes+1;i++){ //On recupere les donnees du fichier
        tableau[i]=malloc(sizeof(char*)*(s.nbr_attributs+1));  //On ajoute 1 pour garder un espace pour le "signal" d'arret (c'est pour le pc)
        if (tableau[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for(j=0;j<s.nbr_attributs+1;j++){ 
            tableau[i][j]=malloc(sizeof(char)*30);
            if(tableau[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
            pos=0;
            while((c= fgetc(fd))!=' ' && c!='\n' && c!='\0' && c!=EOF && pos<29 && c!='\r'){
                tableau[i][j][pos]=c;
                //printf("pos:%d mot:%s\n",pos,tableau[i][j]);
                pos++;
            }
            //printf("i:%d,j:%d:%s\n",i,j,tableau[i][j]);

            tableau[i][j][pos]='\0';
            
            if(c=='\n'){
                break;
            }            
        }
        
    }
    s.tableau=tableau;
    s.liste_etiquette=cherche_etiquette(&s);
    s.liste_attributs_dispo=malloc(sizeof(char*)*(s.nbr_attributs-1)); //-2 car on enleve l'etiquette
    if (s.liste_attributs_dispo == NULL) {
        fprintf(stderr, "Memory allocation failed for liste_attributs_dispo.\n");
        exit(1);
    }
    for(i=0;i<s.nbr_attributs-1;i++){
        /*
        s.liste_attributs_dispo[i]=malloc(sizeof(char)*20);
        if (s.liste_attributs_dispo[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for attribute name.\n");
            exit(1);
        }
        */
        s.liste_attributs_dispo[i] = strdup(s.tableau[0][i]);
        printf("%s\n",s.liste_attributs_dispo[i]);

    }
    fclose(fd);
    return s;
}


void afficher_tableau(stockage s){ 
    for(int i=0;i<s.nbr_exemples+1;i++){
        for(int j=0;j<s.nbr_attributs;j++){
                printf("%s ",s.tableau[i][j]);
            }
        printf("\n");
    }
    printf("nbr attributs : %d\n",s.nbr_attributs);
    printf("nbr exemples : %d\n",s.nbr_exemples);
    printf("nbr etiquette : %d\n",s.nbr_etiquette); 
}

void afficher_etiquette(stockage s){
    //printf("nbr_etiquette i:%d\n",s.nbr_etiquette);

    for(int i=0;i<s.nbr_etiquette;i++){
        //printf("etiquette i:%d,%s\n",i,s.liste_etiquette[i]);
    }
}

void free_stockage(stockage s) {
    // Libérer la mémoire allouée pour chaque attribut de chaque exemple
    for (int i = 0; i < s.nbr_exemples + 1; i++) {
        for (int j = 0; j < s.nbr_attributs + 1; j++) {
            free(s.tableau[i][j]);
        }
        free(s.tableau[i]);
    }

    // Libérer la mémoire pour le tableau de données
    free(s.tableau);

    // Libérer la mémoire pour chaque attribut disponible
    for (int i = 0; i < s.nbr_attributs -1; i++) {
        free(s.liste_attributs_dispo[i]);
    }

    // Libérer la mémoire pour la liste des attributs disponibles
    free(s.liste_attributs_dispo);

    // Libérer la mémoire pour chaque étiquette
    for (int i = 0; i < s.nbr_etiquette; i++) {
        free(s.liste_etiquette[i]);
    }

    // Libérer la mémoire allouée pour la liste des étiquettes
    free(s.liste_etiquette);
}


/*
// Calcul de gain d'entropie

//Recupération des valeurs possibles pour chaque attribut.
attribut Valeur_Attribut(stockage s,int debut,int fin) {
    attribut attrib;
    attrib.nbr_exemples_pris_en_compte=fin-debut;
    printf("Nombre exemple : %d ",attrib.nbr_exemples_pris_en_compte);
    char ***tableau = malloc(sizeof(char **) * (s.nbr_attributs+1));
    int *count = malloc(sizeof(int) * s.nbr_attributs);
    int ***nbr_apparition = malloc(sizeof(int **) * (s.nbr_attributs+1));
    // Vérification des allocations
    if (tableau == NULL || count == NULL || nbr_apparition == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Initialisation des tableaux de pointeurs
    for (int i = 0; i < s.nbr_attributs+1; i++) {
        tableau[i] = malloc(sizeof(char *) *( attrib.nbr_exemples_pris_en_compte));
        nbr_apparition[i] = calloc(attrib.nbr_exemples_pris_en_compte, sizeof(int*));

        if (tableau[i] == NULL || nbr_apparition[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for (int j = 0; j < attrib.nbr_exemples_pris_en_compte; j++) {
            tableau[i][j] = NULL;
            nbr_apparition[i][j] = malloc((s.nbr_etiquette + 1) * sizeof(int));
            for (int etiquette = 0; etiquette < s.nbr_etiquette + 1; etiquette++) {
                nbr_apparition[i][j][etiquette] = 0;
            }
        }
    }
    
    // Parcourir chaque attribut
    for (int i = 0; i < s.nbr_attributs ; i++) {
        int index = 0; // Index pour stocker les valeurs uniques

        // Parcourir chaque exemple pour récupérer les valeurs uniques
        for (int j = 1; j < attrib.nbr_exemples_pris_en_compte +1 ; j++) {
            char *valeur = s.tableau[j][i]; // Valeur de l'attribut dans cet exemple
            int exist = -1; // Variable pour stocker l'indice de la valeur si elle existe déjà, -1 sinon

            // Vérifier si cette valeur existe déjà dans les valeurs attributs
            for (int k = 0; k < index; k++) {
                if (strcmp(valeur, tableau[i][k]) == 0) {
                    exist = k; // La valeur existe déjà, enregistrer l'indice
                    break;
                }
            }

            // Si la valeur n'existe pas déjà, l'ajouter
            if (exist == -1) {
                tableau[i][index] = strdup(valeur);
                exist = index; // Mettre à jour l'indice exist
                index++;
            }

            // Incrémenter le nombre d'apparitions de cette valeur pour l'étiquette correspondante
            for (int etiquette = 0; etiquette < s.nbr_etiquette; etiquette++) {
                if (strcmp(s.liste_etiquette[etiquette], s.tableau[j][s.nbr_attributs - 1]) == 0) {
                    nbr_apparition[i][exist][etiquette + 1]++;
                    break; // Sortir de la boucle dès qu'on trouve l'étiquette correspondante
                }
            }
            nbr_apparition[i][exist][0]++; // Incrémenter le total d'apparitions de cette valeur
        }
        count[i] = index; // Nombre de valeurs uniques pour cet attribut
    }
    
    // Assigner les valeurs à attrib et retourner
    attrib.nbr_valeur_attribut = count;
    attrib.tableau = tableau;
    attrib.nbr_apparition = nbr_apparition;
    return attrib;
}


//Affichage de attribut
void affiche_attribut(attribut a,stockage s){
    for (int i=0;i<s.nbr_attributs;i++){
        printf("Attribut %s :\n",s.tableau[0][i]);
        for (int j=0; j<a.nbr_valeur_attribut[i];j++){
            printf("Valeur %d : %s (Nombre d'apparitions : %d)\n",j+1,a.tableau[i][j],a.nbr_apparition[i][j][0]);
            for (int etiquette=0;etiquette<s.nbr_etiquette;etiquette++){
                printf("Nombre de cette valeur avec etiquette : %s = %d\n",s.liste_etiquette[etiquette],a.nbr_apparition[i][j][etiquette+1]);
            }
        }
        printf("Nombre de valeurs : %d",a.nbr_valeur_attribut[i]);
        printf("\n");
    }
}

//Libere la mémoire de attribut
void free_attribut(attribut a, stockage s) {
    // Libérer la mémoire pour chaque ligne de tableau
    for (int i = 0; i < s.nbr_attributs+1; i++) {
        for (int j = 0; j < a.nbr_exemples_pris_en_compte; j++) {
            free(a.tableau[i][j]);
        }
        free(a.tableau[i]);
    }
    
    // Libérer la mémoire pour tableau
    free(a.tableau);

    // Libérer la mémoire pour les lignes de nbr_apparition
    for (int i = 0; i < s.nbr_attributs+1; i++) {
        for (int j = 0; j < a.nbr_exemples_pris_en_compte; j++) {
            free(a.nbr_apparition[i][j]);
        }
        free(a.nbr_apparition[i]);
    }
    
    // Libérer la mémoire de nbr_apparition
    free(a.nbr_apparition);

    // Libérer la mémoire de count
    free(a.nbr_valeur_attribut);
}
*/

//Calcul de l'entropie
/*
float entropie(int *nbr_apparition, int nbr_etiquette) {
    float entropie = 0.0;
    float total = nbr_apparition[0];
    printf("total : %f\n",total );
    for (int i = 1; i < nbr_etiquette+1; i++) {
        float prob =  (float)(nbr_apparition[i] )/ total;
        printf("prob ; %f\n",prob);
        if (prob != 0.0) {
            entropie = entropie - (prob * log(prob)/log(nbr_etiquette));
            printf("entrop : %f\n",-prob*log(prob)/log(nbr_etiquette));
        }
    }
   
    return entropie;
}

float entropie_etiquette(int ** nbr_apparition, int nbr_etiquette,int nbr_exemples){
    float entropie=0.0;
    float total=nbr_exemples;
    float prob;
    for (int i=0;i<nbr_etiquette;i++){
        prob=nbr_apparition[i][i+1]/total;
        printf("Nombre_apparition : %d",nbr_apparition[i][i+1]);
        printf("prob ; %f\n",prob);
         if (prob != 0.0) {
            entropie = entropie - (prob * log(prob)/log(nbr_etiquette));
            printf("entrop : %f\n",-prob*log(prob)/log(nbr_etiquette));
        }
    }
    return entropie;
}


//Calcul du gain entropique
float gain(attribut attr, stockage s, int set) {
    float gain_entropique = 0.0;
    float entropie_totale = 0.0;
    entropie_totale = entropie_etiquette(attr.nbr_apparition[s.nbr_attributs-1], s.nbr_etiquette,attr.nbr_exemples_pris_en_compte);

    printf("entropie etiquette: %f\n",entropie_totale);
    
    for (int i = 0; i < attr.nbr_valeur_attribut[set]; i++) {
        float prob_valeur = (float) (attr.nbr_apparition[set][i][0] )/ s.nbr_exemples;
        printf("Valeur total : %d\n",attr.nbr_exemples_pris_en_compte);
        printf("Prob_valuer %f\n",prob_valeur);
        printf("Test valeur : %d\n",attr.nbr_apparition[set][i][0]);
        float entropie_sous_ensemble = entropie(attr.nbr_apparition[set][i], s.nbr_etiquette);
        printf("Entropie_sous_ensemnble : %f\n",entropie_sous_ensemble);
        gain_entropique += prob_valeur * entropie_sous_ensemble;
    }
    printf("Gain entropique : %f\n",gain_entropique);
    gain_entropique = entropie_totale - gain_entropique;
    
    return gain_entropique;
}

int Choix_attribut_noeud(attribut attr, stockage s){
    //Parcours les attributs disponible et prend l'attribut qui a le gain entropique le plus élevé.
    float max_gain = -1;
    int max_index = -1;
    for(int i = 0; i < s.nbr_attributs - 1; i++){ //Prend en compte tous les attributs actuellement=CACA
        float g = gain(attr, s, i);
        if(g > max_gain){
            max_gain = g;
            max_index = i;
        }
    }
    return max_index;
}


void Trie_Stockage_attribut(stockage s, int attributchoisie,int debut, int fin){
    //Trie la structure stockage pour separer les exemples selon le critère indiqué de la case debut à la case fin.
    //ENleve egalement l'attribut des attributs disponible.
}


*/




