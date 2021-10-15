%{
#include "simple-expr.tab.h"
#include <stdlib.h>
#include <stdbool.h>
extern int yylval;

// FROM https://stackoverflow.com/questions/1756275/bison-end-of-file
bool term = false;
#define yyterminate() return (term = !term) ? END : YY_NULL   
%}
%%
[0-9]+      { yylval = atoi(yytext); return NUMBER;}
[a-z]+      { yylval = yytext[0]; return NAME;}
[ \t\n]     
.           return yytext[0];
%%