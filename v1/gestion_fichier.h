#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** separateur(char * phrase,char sep){
    char **tab;
    int i=0,j=0,pos=0,nbr_mot=0;
    //On compte le nombre de mot en fonction du separateur
    while(phrase[i]!='\0'){
        if(phrase[i]==sep){
            nbr_mot++;
        }
        i++;
    }
    i=0;
    tab=malloc(sizeof(char *)*nbr_mot+1); //On initialise le tableau de chaine de caractère
    while(phrase[i]!='\0' && j<=nbr_mot){
        tab[j]=malloc(sizeof(char)*45); //On initialise un mot temporaire
        while(phrase[i]!=sep && phrase[i]!='\0'){ //On crée le mot en enlevant le séparateur
            tab[j][pos]=phrase[i]; 
            pos++;
            i++;    
    }   
        tab[j][pos]='\0'; 
        pos=0;
        j++;
        i++;     
    }
    return tab; 
}


