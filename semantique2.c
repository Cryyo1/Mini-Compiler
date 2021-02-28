#include<string.h>
#include<stdio.h>
#include<stdlib.h>
/******************************************************************************/
typedef struct{
char* NomEntite;
char* CodeEntite;
char* TypeEntite;
char* isConst;
int   taille;
char* value;
}typeTS;
/******************************************************************************/
typedef struct node{
	typeTS element;
	struct node *next; 
}node;
/******************************************************************************/
typedef node* list;
list head=NULL;
/******************************************************************************/
list newNode(char* entite,char* code){

   list newnode = (node*)malloc(sizeof(node));
   newnode->element.NomEntite =strdup(entite);
   newnode->element.CodeEntite=strdup(code);
   newnode->element.TypeEntite=strdup("");
   newnode->element.value=strdup("");
   newnode->element.isConst=strdup("Not_Const");
   newnode->next = NULL;
   return newnode;
}
/******************************************************************************/
void insert(char* entite,char* code){
	list temp,curr;

	temp = newNode(entite,code);
	curr = head;

	if (head == NULL) {
	    head = temp;
	    return;
	}
	int i=0;
    while (curr->next != NULL){
        curr = curr->next;
    }
    
    curr->next = temp;
    return;
}
/******************************************************************************/
int recherche(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) ==0)
          return 1;
      curr=curr->next;
    }
    return 0;
}
/******************************************************************************/
void Afficher(){
      list curr;
      curr=head;
      printf("/************************************ Table des symboles ***************************************\n");
      printf("------------------------------------------------------------------------------------------------\n");
      printf("|  NomEntite  |  CodeEntite     |    TypeEntite     |     taille   |    valeur   |  constante  |\n");
      printf("------------------------------------------------------------------------------------------------\n");
      while (curr != NULL){
        printf("|%13s| %15s |%19s|%14d|%13s|%13s|\n",curr->element.NomEntite,
        curr->element.CodeEntite,curr->element.TypeEntite,
        curr->element.taille,curr->element.value,curr->element.isConst);
        printf("------------------------------------------------------------------------------------------------\n");
        curr=curr->next;
      } 

}
/******************************************************************************/
void insertType(char* entite, char* type){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) ==0){
          curr->element.TypeEntite=strdup(type);
          return;
      }
      curr=curr->next;
    }  
}
/*****************************************************************************/
void insertTaille(char* entite, int taille){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) ==0){
          curr->element.taille=taille;
          return;
      }
      curr=curr->next;
    }  
}
/*****************************************************************************/
void insertValue(char* entite, char* value){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) ==0){
          curr->element.value=strdup(value);
          return;
      }
      curr=curr->next;
    }  
}
/*****************************************************************************/
void insertIsConst(char* entite, char* constante){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) ==0){
          curr->element.isConst=strdup(constante);
          return;
      }
      curr=curr->next;
    }  
}

/******************************************************************************/
int doubleDeclaration(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0)
          return 0;
      curr=curr->next;
    }  
    return 1;
}
/*********************************************************************************/
int ModifierConst(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0){
          if(strcmp(curr->element.isConst,"Not_Const")==0)
            return -1;
      }
      curr=curr->next;
    }  
}

int main(){
    insert("chakib","boudjema");
    insertIsConst("chakib","Const");
    insertValue("chakib","15");
    printf("%d",ModifierConst("chakib"));
}