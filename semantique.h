#include<stdio.h>
#include<stdlib.h>
#include <string.h>
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
      if(strcmp(curr->element.NomEntite,entite) == 0)
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
      if(strcmp(curr->element.NomEntite,entite) == 0){
         if(strcmp(curr->element.TypeEntite,"")==0)
            return 0;
          else
            return 1;
      }
      curr=curr->next;
    }  
}
/*********************************************************************************/
int ModifyConst(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0){
          if(strcmp(curr->element.isConst,"Not_Const")==0){
                return -1;
          }
          else{
              if(strcmp(curr->element.value,"")==0)
                return -1;
              else
                return 1; 
          }
      }
      curr=curr->next;
    }  
}

/****************************************************************************/
int idfNotDeclared(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0){
        if(strcmp(curr->element.TypeEntite,"")==0)
              return 1;
        else
          return 0;

    }
      curr=curr->next;
    }  

}
/*******************************************************************************/
int indexOutOfBound(char* entite,int index){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0){
        if(index > curr->element.taille || index <= 0)
          return 1;
        else 
          return 0;
      }
      curr=curr->next;
    }  
  
}
/************************************************************************************/
int indexOutOfBoundV2(char* entite,char* variable){
    list curr;
    curr=head;
    list tableau,var;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0){
        tableau=curr;
      }
      curr=curr->next;
    } 
    curr = head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,variable) == 0){
        var=curr;
      }
      curr=curr->next;
    }

    if(atoi(var->element.value) > tableau->element.taille || atoi(var->element.value) <= 0)
      return 1;
    else 
      return 0;
}  
/**************************************************************************************/
char* getType(char* entite){
    list curr;
    curr=head;
    char *type;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0)
          type= strdup(curr->element.TypeEntite);
      curr=curr->next;
    }
    return type;
}
/**************************************************************************************/
char* getValue(char* entite){
    list curr;
    curr=head;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0)
          return curr->element.value; 
      curr=curr->next;
    }
    return "";
}
/***************************************************************************************/
int formatage(char *texte, char *ls_idf[20],int taille){
  int i,j;
  char * signes[20], *signe;
  char *ls_types [20];
  char* type;
  for(i=0;i<taille;i++){
    type = getType(ls_idf[taille-i-1]);
    ls_types[i]=strdup(type);
  }
  j=0;
  for(i=j;i<=strlen(texte);i++){
    signe = "";
    if(texte[i] == '%'){
      signe = strdup("%");
      if(texte[i+1] == 'f' || texte[i+1] == 'd' || texte[i+1] == 's'){
        strncat(signe, &texte[i+1],1);
        signes[j]= signe;
        j++;
      }
    }
  }
  if(j!=taille) {
    return 0;
  }
  if(j==taille){
    for(i=0;i<j;i++){
      if(strcmp(signes[i],"%d")==0 && strcmp(ls_types[i],"Entier")==0 || strcmp(signes[i],"%f")==0 && strcmp(ls_types[i],"reel")==0 || strcmp(signes[i],"%s")==0 && strcmp(ls_types[i],"chaine")==0) {
        }
      else {
        return 0;
      }
    }
  }
  return 1;
}
/******************************************************************************************/
int typeMismatch(char *ls_idf_exp[20],char* lef_idf,int taille){
  char* type=getType(lef_idf);
  int i;
  for(i=0;i<taille;i++){
      if(strcmp(type,getType(ls_idf_exp[i])) != 0)
        return 1;
  }
  return 0;

}
/***********************************************************/
int valueNotInitialized(char* entite){
    list curr;
    curr=head;
    char *type;
    while (curr != NULL)
    {
      if(strcmp(curr->element.NomEntite,entite) == 0)
          if(strcmp(curr->element.value,"") == 0)
            return 1;
      curr=curr->next;
    }
    return 0;
}


