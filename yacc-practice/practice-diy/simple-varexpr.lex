%{
#include "simple-varexpr.tab.h"
#include <math.h> 
%}

%%
[0-9]+      {yylval.rvalue = atoi(yytext); return NUMBER; }
[a-z]       {yylval.lvalue = yytext[0]; return NAME; }
[ \t\n]       ;
.           return yytext[0];
%%