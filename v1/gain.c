#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct noeud{
    void* data;
    struct noeud* suiv;
} noeud;

typedef struct fileN{
    noeud* premier;
    noeud* dernier;
    int count;
} fileN;

fileN* initfileN(){
    fileN* fileN= (fileN*) malloc(sizeof(fileN));

    fileN->premier=NULL;
    fileN->dernier=NULL;
    fileN->count=0;
    return fileN;

}

void EnFileN(fileN ** fileN){
    noeud* noeud=(noeud*)malloc(sizeof(noeud));
    
    noeud->data=NULL;
    noeud->suiv=NULL;
    
    if ((fileN)->premier !=NULL){
        (*fileN)->dernier->suiv=noeud;
        (*fileN)->dernier=noeud;
    }
    else{
        (*fileN)->premier = noeud;
		(*fileN)->dernier = noeud;
    }
    (*fileN)->count++;

}

void* defileN(fileN* fileN){
    if(fileN->premier==NULL){
        return NULL;
    }
    noeud* noeud = fileN->premier;
    void* data=noeud->data;

    if (fileN->premier==fileN->dernier){
        fileN->dernier=NULL;
    }

    fileN->premier=noeud->suiv;
    fileN->count--;
    free(noeud);
    return data;
}

void FreeNoeud(fileN* fileN){
    noeud* cur=fileN->premier;
    noeud* tmp;

    while(cur){
        tmp=cur->suiv;
        if(cur->data){
            free(cur->data);
        }
        cur=tmp;
    }
}

void FreeFileN(fileN* fileN){
    noeud* cur= fileN;
    noeud* tmp;
    while(cur){
        tmp=cur->suiv;
        free(cur);
        cur=tmp;
    }
    free(fileN);
}
