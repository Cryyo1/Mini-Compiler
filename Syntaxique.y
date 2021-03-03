%{
int nbligne=1;
int nbcolonne=1;
int sauvValue=0;
float sauvValueReel=0;
char* sauvOp="";
char* sauvValueStr="";
char type[20],constante[20],tmp[20];
char *ls_idf[20],*list_idf_exp[20];
int i=0,k=0;
%}

%union{
	int entier;
	float reel;
	char* str;
}

%start S
%token 	mc_import <str>bib_io <str>bib_lang pvg err
	   	mc_class mc_private mc_public mc_protected <str>idf
	   	mc_entier mc_reel mc_chaine aco_ouv aco_ferm
		<entier>valeur <reel>valeur_reel <str>idf_tab crochet_ferm crochet_ouv vrgl mc_const 
		affect mc_somme mc_soust mc_multi mc_div
		mc_egal mc_inf mc_sup mc_inf_egal mc_sup_egal mc_not_egal mc_for
		parenth_ouv parenth_ferm mc_out mc_in mc_main <str>mc_text
%%

S:LISTE_BIB CLASS aco_ouv LISTE_DEC mc_main parenth_ouv parenth_ferm aco_ouv CORPS aco_ferm aco_ferm
		{printf("syntaxe correcte\n");}

LISTE_BIB: BIB LISTE_BIB
			|
;

BIB: mc_import NOM_BIB pvg

;
NOM_BIB:bib_io {
	insert($1,"idf_bib");
	insertType($1,"Sans_type");
	insertTaille($1,0);
	insertValue($1,"0");
	insertIsConst($1,"non_const");
}
	|bib_lang {
	insert($1,"idf_bib");
	insertType($1,"Sans_type");
	insertTaille($1,0);
	insertValue($1,"0");
	insertIsConst($1,"non_const");
}
   
;

CLASS: MODIFCATEUR mc_class idf
		{
		insertType($3,"sans_type");
		insertTaille($3,0);
		}


;
MODIFCATEUR:mc_private
			|mc_protected
			|mc_public
			|

;

CORPS: LISTE_INST

;

LISTE_DEC: PARTIE_DEC LISTE_DEC
			|

;

PARTIE_DEC: TYPE_VARIABLE LISTE_IDF pvg
			|TYPE_VARIABLE LISTE_IDF_TAB pvg
			|mc_const TYPE_VARIABLE idf affect valeur pvg
			{	
				if(doubleDeclaration($3)== 0){
					insertType($3,type);
					insertTaille($3,1);
					sprintf(tmp, "%d", $5);
					insertValue($3,tmp);
					insertIsConst($3,"Const");
				}else{
					printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
					YYACCEPT;
				}
			}
			|mc_const TYPE_VARIABLE idf pvg 
			{	if(doubleDeclaration($3)== 0){
					insertType($3,type);
					insertTaille($3,1);
					insertIsConst($3,"Const");
				}else{
					printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
					YYACCEPT;
				}
			}
;

LISTE_IDF: idf vrgl LISTE_IDF
			{	if(doubleDeclaration($1)== 0){
					insertType($1,type);
					insertTaille($1,1);
				}else{
					printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
					YYACCEPT;
				}
			}
			|idf	
			{	if(doubleDeclaration($1)== 0){
					insertType($1,type);
					insertTaille($1,1);
				}else{
					printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
					YYACCEPT;
				}
			}

;

LISTE_IDF_TAB:idf_tab crochet_ouv valeur crochet_ferm vrgl LISTE_IDF_TAB
				{
					if(doubleDeclaration($1)== 0){
						insertType($1,type);
						insertTaille($1,$3);
					}else{
						printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
						YYACCEPT;
					}
				}
			|idf_tab crochet_ouv valeur crochet_ferm
				{
					if(doubleDeclaration($1)== 0){
						insertType($1,type);
						insertTaille($1,$3);
					}else{
						printf("erreur, la variable est deja declarer : %d !!!! \n",nbligne);
						YYACCEPT;
					}
				}

;

TYPE_VARIABLE: mc_chaine{strcpy(type,$1);}
			|mc_entier	{strcpy(type,$1);}
			|mc_reel	{strcpy(type,$1);}

;

LISTE_INST: INSTRU LISTE_INST 
			|

;

INSTRU: LISTE_AFFECT
		|BOUCLE
		|IN
		|OUT
		
	

;

LISTE_IDF_IO: idf vrgl LISTE_IDF_IO {
	if(idfNotDeclared(strdup($1))==0){
					
					ls_idf[i]=$1;
							i++;
							
				} else{
					printf("Erreur semantique : variable inexistante");
					YYACCEPT;
				}
}
			|idf {
				if(idfNotDeclared(strdup($1))==0){
					
					ls_idf[i]=$1;
							i++;
							
				} else{
					printf("Erreur semantique : variable inexistante");
					YYACCEPT;
				}
			}

;

IN: mc_in parenth_ouv mc_text vrgl LISTE_IDF_IO parenth_ferm pvg {
	if(recherche("ISIL.io")==0){
		printf("Erreur semantique: absence de bibiliotheque \"ISIL.io \"");
		YYACCEPT;
	}
	if(formatage($3,ls_idf,i)==0){
		printf("Erreur semantique de formatage\n");
		YYACCEPT;
	}


}

;

OUT: mc_out parenth_ouv mc_text vrgl LISTE_IDF_IO parenth_ferm pvg {
	if(recherche("ISIL.io")==0){
		printf("Erreur semantique: absence de bibiliotheque \"ISIL.io \"");
		YYACCEPT;
	}
	if(formatage($3,ls_idf,i)==0){
		printf("Erreur semantique de formatage\n");
		YYACCEPT;
	}
}
	|mc_out parenth_ouv mc_text parenth_ferm pvg {
	if(formatage($3,ls_idf,i)==0){
		printf("Erreur semantique de formatage\n");
		YYACCEPT;
	}
}

;



LISTE_AFFECT:idf affect EXPRESSION pvg{			
				if(ModifyConst($1) == 1){
					printf("Erreur semantique : impossible de changer la  valeur d'une constante !!!!\n");
					YYACCEPT;
				}
				if(idfNotDeclared($1)== 1){
					printf("Erreur semantique : Variable non Declarer !!!!\n");
					YYACCEPT;
				}
				if(strcmp(getType($1),"Entier") == 0){
					sprintf(tmp,"%d",sauvValue);
					insertValue($1,tmp);
					sauvValue = 0;
				}else{
					if(strcmp(getType($1),"reel") == 0){
						sprintf(tmp,"%f",sauvValueReel);
						insertValue($1,tmp);
						sauvValueReel = 0;
					}else{
						insertValue($1,sauvValueStr);
						sauvValueStr = "";
					}

				}

				if(typeMismatch(list_idf_exp,$1,k)== 1){
					printf("Erreur semantique :  Non compatibilite de type !!!!\n");
					YYACCEPT;
				}
				
			}
			|idf_tab crochet_ouv idf crochet_ferm affect EXPRESSION pvg {
				if(indexOutOfBoundV2($1,$3)==1){
					printf("Erreur semantique : Index superierur a la taille du tableau ou inferierur a 0 !!!!\n");
					YYACCEPT;
				}
			}
			|idf_tab crochet_ouv valeur crochet_ferm affect EXPRESSION pvg{
				if(indexOutOfBound($1,$3)==1){
					printf("Erreur semantique : Index superierur a la taille de tableau ou inferierur a 0 !!!!\n");
					YYACCEPT;
				}
			} 
;


EXPRESSION:	TYPE_VALEUR
			|EXPRESSION OPERATION EXPRESSION{
				if(strcmp(sauvOp,"/")== 0 && sauvValue==0){
					printf ("Erreur semantique : division par zero !!!!!\n");
					YYACCEPT;
				} 
			}
			|idf{
				if(valueNotInitialized($1)){
					printf ("Erreur semantique : valeur de %s n'est pas intialiser !!!!!\n",$1);
					YYACCEPT;
				}
				list_idf_exp[k]=$1;
				k++;
			}
			|parenth_ouv EXPRESSION parenth_ferm

;

TYPE_VALEUR:valeur{
				sauvValue=$1;
			}
			|valeur_reel{sauvValueReel=$1;}
			|mc_text{sauvValueStr=strdup($1);}

;

OPERATION: 	mc_somme{sauvOp=strdup($1)}
			|mc_soust{sauvOp=strdup($1)}
			|mc_multi{sauvOp=strdup($1)}
			|mc_div{sauvOp=strdup($1)}

;


BOUCLE:mc_for parenth_ouv INIT pvg CONDITION pvg INCREMENT parenth_ferm aco_ouv LISTE_INST aco_ferm

;

INIT:idf affect TYPE_VALEUR

;

CONDITION:idf LISTE_CONDITION TYPE_VALEUR
			|idf LISTE_CONDITION idf

;

INCREMENT:idf mc_somme mc_somme

;

LISTE_CONDITION:mc_egal
				|mc_inf
				|mc_sup
				|mc_inf_egal
				|mc_sup_egal
				|mc_not_egal

;
	
%%
main(){
	yyparse();
	Afficher();
}

yywrap()
{}

yyerror(char*msg){
    printf("Erreur Syntaxique dans votre code dans la ligne : %d , colonne : %d!!!! ",nbligne,nbcolonne);
}
