flex Lexicale.l
bison -d Syntaxique.y
gcc lex.yy.c Syntaxique.tab.c -lfl -ly -o compilateur