%{
#include "exprdefs.h"
#include "sexpr-codegen.tab.h"
#include <stdlib.h>
%}
%%

[0-9]+   { yylval.number = atoi(yytext); return NUMBER; }
[ \t\n]  ;
[a-zA-Z\_]+  {yylval.name = new string(yytext); return NAME;}
.        return yytext[0];
%%
