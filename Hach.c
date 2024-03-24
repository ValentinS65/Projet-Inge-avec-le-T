#include <stdio.h>
#include <stdlib.h>
#include<string.h>


#define MAX 500 //Taille de la table de hachage

//FONCTION DE HASHAGE ~demander quel utilisation
int hash_code(char* str){ //Calcule du Code hash pour l'indice du tableau.
  int i=0;
  for (int j=0;str[j];j++){
    i+=str[j];
  }
  return i%MAX;
}



//Defini les élements de la table hashage :
typedef struct Hash_item{
  char* key; //Clé de la relation
  char* value; // Data de la relation
}Hash_item;

//Implementation de la structure ListechaineH 
typedef struct ListeChaineH{
  Hash_item* item;
  struct ListeChaineH* next;
}ListeChaineH;

//Defini la table de hashage
typedef struct HashTable{
  int size; //taille de la table
  int count; //nombre d'element
  //Tableau de pointeurs sur les Ht_item
  Hash_item** items;
  ListeChaineH** tab_collision;

}HashTable;


//Implementation du TDA Listechaine 
//Initialisation de la liste chainee
ListeChaineH* Init_ListeChaineH(){
  ListeChaineH* list=(ListeChaineH*) malloc(sizeof(ListeChaineH));
  if (list==NULL){
    exit(EXIT_FAILURE); //Erreur allocation
  }
  list->item = NULL;
  list->next = NULL;
  return list;
}

//Insertion valeur à la fin
//A FAIRE : MODIFICATION INSERTION AU DEBUT DE LA LISTE POUR TEMPS CONSTANT
ListeChaineH*  ListeChaineH_insert(ListeChaineH* list,Hash_item* item){
  if (!list){
    ListeChaineH* head= Init_ListeChaineH();
    head->item=item;
    head->next=NULL;
    list=head;
    return list;
  }
  else if(list->next==NULL){
    ListeChaineH* maillon=Init_ListeChaineH();
    maillon->item=item;
    maillon->next=NULL;
    list->next=maillon;
    return list;
  }
  else{//Ca a changer insertion au debut plutot qu'a la fin
    ListeChaineH* temp=list;
    while(temp->next->next){
      temp=temp->next;
    }
    ListeChaineH* maillon=Init_ListeChaineH();
    maillon->item=item;
    maillon->next=NULL;
    temp->next=maillon;
    return list;
  }
}



//Suppression de la liste
void free_ListeChaineH(ListeChaineH* list){
    ListeChaineH* temp = list;
    while (temp != NULL) {
        ListeChaineH* nextNode = temp->next;
        if (temp->item != NULL) {
            // Libérer la mémoire des membres de l'élément
            free(temp->item->key);
            free(temp->item->value);
            // Libérer la mémoire de l'élément lui-même
            free(temp->item);
        }
        // Libérer la mémoire du nœud de la liste chaînée
        free(temp);
        temp = nextNode;
    }
}



//Createur des élements.
Hash_item* Init_item(char* key, char*value){
  Hash_item* item= (Hash_item*)malloc(sizeof(Hash_item));
  if(item==NULL){
    exit(EXIT_FAILURE);//echec allocation
  }
  item->value=(char*)malloc(strlen(value)+1); //allocation chaine de caractère pour clé
  item->key=(char*)malloc(strlen(value)+1);
  if (item->key==NULL || item->value==NULL) {
    exit(EXIT_FAILURE); //echec allocation
  }
  strcpy(item->key,key); //copie de la clé
  strcpy(item->value,value);//copie de la valeur
  return item;
}
//initialisation de la table de collision
ListeChaineH** Init_tab_collision(HashTable * table){
  ListeChaineH** buckets= (ListeChaineH**)malloc(table->size*sizeof(ListeChaineH*));
  if (buckets==NULL){
    exit(EXIT_FAILURE); //echec allocation
  }
  for (int i=0; i<table->size; i++){
    buckets[i]=NULL;//initialisation à nul.
  }
  return buckets;
}

//Liberation de la table de collision
void free_tab_collision(HashTable* table){
  ListeChaineH** buckets=table->tab_collision;
  for (int i=0;i<table->size;i++){
    free_ListeChaineH(buckets[i]);
  }
  free(buckets);
}

//Createur de la table
HashTable* Init_table(int size){
  HashTable* tableH=(HashTable*)malloc(sizeof(HashTable));//Alloue la mémoire pour la table
  if (tableH==NULL){
    exit(EXIT_FAILURE);//Echec de l'allocation
  }
  tableH->size=size; //fixe la taille du tableau
  tableH->items=(Hash_item**)malloc(tableH->size*sizeof(Hash_item*));//Alloue la mémoire pour le tableau sur lequel pointe la table
  if(tableH->items==NULL){
    exit(EXIT_FAILURE);//Echec de l'allocation
  }
  for(int i=0;i<tableH->size;i++){
    tableH->items[i]=NULL; //initialisation des valeurs du tableauH
  }
  tableH->tab_collision=Init_tab_collision(tableH);
  return tableH;
}

//Fonctions de libérations mémoire :

//-libère un item
void free_item(Hash_item* item){
  free(item->key);
  free(item->value);
  free(item);
}
//-libère la table
void free_tableH(HashTable* tableH){
  free_tab_collision(tableH);
  for (int i=0;i<tableH->size;i++){
    Hash_item* item=tableH->items[i];
    if (item!=NULL){
      free_item(item);
    }
  }
  free(tableH->items);
  free(tableH);
}

//Fonctions du TDA hashTab
//Fonction pour gerer les colision dans la table(utilisation de liste chainée)
void collision(HashTable* tableH,int h, Hash_item* item){
  ListeChaineH* tete=tableH->tab_collision[h];
  if (tete==NULL){
    tete=Init_ListeChaineH();
    tete->item=item;
    tableH->tab_collision[h]=tete;
  }
  else{
    while(tete!=NULL){
      if (strcmp(tete->item->key,item->key)==0){
        free_item(tete->item);
        tete->item=item;
        return;
      }
      tete=tete->next;
    }
    tableH->tab_collision[h]=ListeChaineH_insert(tete,item);
  }
}
//Insert clé
void hash_insert(HashTable* tableH,char* key,char*value){
  Hash_item* item=Init_item(key,value);
  int h=hash_code(key);//calcule de l'indice h
  Hash_item* ancien= tableH->items[h];
  if (ancien==NULL){ //rien à cette index
    //insertion
    tableH->items[h]=item;
    tableH->count++;
  }
  else{
    //si clé dejà existente mise à jour de la valeur :
    if (strcmp(ancien->key,key)==0){
      free_item(ancien);
      tableH->items[h]=item;
    }
    else{
      collision(tableH,h,item); //gere la collision liste chainé à implementer
    }
  }
}

//Recherche valeur pour clé

char* hash_find(HashTable* table,char* key){
  int h=hash_code(key); //calcule de l'indice H
  Hash_item* item=table->items[h]; //recupération de la valeur à l'indice h
  ListeChaineH* tete=table->tab_collision[h];
  while (item!=NULL){ //existence d'une valeur à l'indice H
    if(strcmp(item->key,key)==0){ //la clé se trouvant à l'indice H est elle la bonne
      return item->value; //recupération de la valeur
    }
    if (tete==NULL){
      return NULL;
    }
    item=tete->item;
    tete=tete->next;
  }
  return NULL; //clé inexistante

}

//Fonction affichage
//Affiche une recherche pour les test surtout
void print_search(HashTable *table,char *key){
  char *val;
  if ((val=hash_find(table,key))==NULL){
    printf("Key: %s n'existe pas\n",key);
    return;
  }
  else{
    printf("Key:%s - valeur : %s \n ",key,val);
  }
}

//affiche la table
void print_HashT(HashTable* tableH)
{
  printf("\nHash-Table\n");
  printf("-----------------------\n");
  for (int i=0;i<tableH->size;i++){
    if(tableH->items[i]){
      printf("Clé: %s - Valeur:%s \n", tableH->items[i]->key,tableH->items[i]->value);
    }
  }
  printf("---------------------\n");
}


int main(){
  HashTable *ht = Init_table(MAX);
  hash_insert(ht, (char *)"2", (char *)"1 endroit");
  hash_insert(ht, (char *)"2", (char *)"2 eme endroit");
  hash_insert(ht, (char *)"Hel", (char *)"3 eme endroit");
  hash_insert(ht, (char *)"Cau", (char *)"4 eme endroit");
  hash_insert(ht, (char *)"Cau", (char *)"5 eme endroit");
  hash_insert(ht, (char *)"Hel", (char *)"6 eme endroit");
  hash_insert(ht, (char *)"Cau", (char *)"7 eme endroit");
  hash_insert(ht, (char *)"4", (char *)"1 endroit");
  hash_insert(ht, (char *)"5", (char *)"2 eme endroit");
  hash_insert(ht, (char *)"Helkk", (char *)"3 eme endroit");
  hash_insert(ht, (char *)"Caukdfv", (char *)"4 eme endroit");
  hash_insert(ht, (char *)"Casdgdu", (char *)"5 eme endroit");
  hash_insert(ht, (char *)"Hecxbl", (char *)"6 eme endroit");
  hash_insert(ht, (char *)"Cauvsdfb", (char *)"7 eme endroit");
  print_search(ht, (char *)"1");
  print_search(ht, (char *)"2");
  print_search(ht, (char *)"3");
  print_search(ht, (char *)"Hel");
  print_search(ht, (char *)"Cau"); // Collision!
  print_HashT(ht);
  print_HashT(ht);
  free_tableH(ht);
  return 0;
}