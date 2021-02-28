%{
#include<stdio.h>
#include<stdlib.h>
#include "Syntaxique.tab.h"
#include "semantique.h"
#include<string.h>
extern int nbligne;
extern int nbcolonne;
extern YYSTYPE yylval;
%}

LETTRE [a-zA-Z]
CHIFFRE [0-9]
IDF "$"{LETTRE}({LETTRE}|{CHIFFRE}|_)*
IDF_TAB "@"{LETTRE}({LETTRE}|{CHIFFRE})*
TEXT \"[^"]*\"

VALEUR {CHIFFRE}+
VALEUR_REEL ({CHIFFRE}+)(",")({CHIFFRE}+)


%%
import          {   nbcolonne+=yyleng;
                    return mc_import;
                }
ISIL.io         {   nbcolonne+=yyleng;
                    return bib_io;
                }
ISIL.lang       {   nbcolonne+=yyleng;
                    return bib_lang;
                }
";"             {   nbcolonne+=yyleng;
                    return pvg;
                }

class           {   nbcolonne+=yyleng;
                    return mc_class;
                }
private         {   nbcolonne+=yyleng;
                    return mc_private;
                }
public          {   nbcolonne+=yyleng;
                    return mc_public;
                }
protected       {   nbcolonne+=yyleng;
                    return mc_protected;
                }
{IDF}           {   if(yyleng<20 && recherche(yytext)==0){
                        insert(yytext,"idf");
                        nbcolonne+=yyleng;
                        yylval.str=strdup(yytext);
                        return idf;
                    }
                    if(yyleng>20){
                        printf("Identificateur a plus de 20 caracteres");
                    }
                    yylval.str=strdup(yytext);
                    return idf;
                }

Entier          {   nbcolonne+=yyleng;
                    yylval.str=strdup("Entier");
                    return mc_entier;
                }
Reel            {   nbcolonne+=yyleng;
                    yylval.str=strdup("reel");
                    return mc_reel;
                }
Chaine          {   nbcolonne+=yyleng;
                    yylval.str=strdup("chaine");
                    return mc_chaine;
                }
CONST           {   nbcolonne+=yyleng;
                    return mc_const;
                }
{VALEUR}        {   yylval.entier=atoi(yytext);
                    return valeur;
                }
{VALEUR_REEL}   {   yylval.reel=atof(yytext);
                    return valeur_reel;
                }

{IDF_TAB}       {   if(yyleng<20 && recherche(yytext)==0){
                        insert(yytext,"idf_tab");
                        nbcolonne+=yyleng;
                        yylval.str=strdup(yytext);
                        return idf_tab;
                    }
                    if(yyleng>20){
                        printf("Identificateur a plus de 20 caracteres");
                    }
                    yylval.str=strdup(yytext);
                    return idf_tab;
                }
"{"             {   nbcolonne+=yyleng;
                    return aco_ouv;
                }
"}"             {   nbcolonne+=yyleng;
                    return aco_ferm;
                }
"]"             {   nbcolonne+=yyleng;
                    return crochet_ferm;
                }
"["             {   nbcolonne+=yyleng;
                    return crochet_ouv;
                }
","             {   nbcolonne+=yyleng;
                    return vrgl;
                }


":="            {   nbcolonne+=yyleng;
                    return affect;
                }
"+"             {   yylval.str=strdup(yytext);
                    nbcolonne+=yyleng;
                    return mc_somme;
                }
"/"             {   yylval.str=strdup(yytext);
                    nbcolonne+=yyleng;
                    return mc_div;
                }
"*"             {   yylval.str=strdup(yytext);
                    nbcolonne+=yyleng;
                    return mc_multi;
                }
"-"             {   yylval.str=strdup(yytext);
                    nbcolonne+=yyleng;
                    return mc_soust;
                }

"="             {   nbcolonne+=yyleng;
                    return mc_egal;
                }
"<"             {   nbcolonne+=yyleng;
                    return mc_inf;
                }
">"             {   nbcolonne+=yyleng;
                    return mc_sup;
                }
"<="            {   nbcolonne+=yyleng;
                    return mc_inf_egal;
                }
">="            {   nbcolonne+=yyleng;
                    return mc_sup_egal;
                }
"!="            {   nbcolonne+=yyleng;
                    return mc_not_egal;
                }
for             {   nbcolonne+=yyleng;
                    return mc_for;
                }
"("             {   nbcolonne+=yyleng;
                    return parenth_ouv;
                }
")"             {   nbcolonne+=yyleng;
                    return parenth_ferm;
                }
{TEXT}          {   nbcolonne+=yyleng;
                    return mc_text;
                }
IN              {   nbcolonne+=yyleng;
                    return mc_in;
                }
OUT             {   nbcolonne+=yyleng;
                    return mc_out;
                }
main            {   nbcolonne+=yyleng;
                    return mc_main;
                }



"##"[^#]*"##"


[  \t]      ;
[\n] {  nbcolonne=1;
        nbligne++;}


. {printf("erreur lexicale a la ligne %d ,colonne %d :%s \n",nbligne,nbcolonne,yytext);
    return err;}
