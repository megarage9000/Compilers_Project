%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
%}

%token ID

%left '-''+'
%left '*''/'
%left '('')'
%left UMINUS

%%

top: e ';' { printf("\n"); exit(EXIT_SUCCESS); }

e: e '+' e { printf("+"); }
 | e '-' e { printf("-"); }
 | e '*' e { printf("*"); }
 | e '/' e { printf("/"); }
 | '(' e ')'
 | ID  { printf("%c", $1); }
 | '-' e %prec UMINUS { printf("-"); } 
 ;

%%

yylex() {
    int c=getchar();
    while ((c == ' ') || (c == '\n') || (c == '\t')) {
        /* skip whitespace */  
        c = getchar();
    }
    if (islower(c)) {
        yylval = c;
        return(ID);
    }
    return(c);
}