
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     mc_import = 258,
     bib_io = 259,
     bib_lang = 260,
     pvg = 261,
     err = 262,
     mc_class = 263,
     mc_private = 264,
     mc_public = 265,
     mc_protected = 266,
     idf = 267,
     mc_entier = 268,
     mc_reel = 269,
     mc_chaine = 270,
     aco_ouv = 271,
     aco_ferm = 272,
     valeur = 273,
     valeur_reel = 274,
     idf_tab = 275,
     crochet_ferm = 276,
     crochet_ouv = 277,
     vrgl = 278,
     mc_const = 279,
     affect = 280,
     mc_somme = 281,
     mc_soust = 282,
     mc_multi = 283,
     mc_div = 284,
     mc_egal = 285,
     mc_inf = 286,
     mc_sup = 287,
     mc_inf_egal = 288,
     mc_sup_egal = 289,
     mc_not_egal = 290,
     mc_for = 291,
     parenth_ouv = 292,
     parenth_ferm = 293,
     mc_out = 294,
     mc_in = 295,
     mc_main = 296,
     mc_text = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 13 "Syntaxique.y"

	int entier;
	float reel;
	char* str;



/* Line 1676 of yacc.c  */
#line 102 "Syntaxique.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


