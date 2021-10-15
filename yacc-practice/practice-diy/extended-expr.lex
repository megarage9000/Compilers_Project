%{
#include "extended-expr.tab.h"
#include <stdlib.h>
%}

%%
log         {return T_LOG;}
exp         {return T_EXP;}
sqrt        {return T_SQRT;}
[0-9]+      {yylval.rvalue = atof(yytext); return T_NUMBER; }
[0-9]+\.[0-9]+   {yylval.rvalue = atof(yytext); return T_DOUBLE;}
[ \t\n]       ;
[a-z]       {yylval.lvalue = yytext[0]; return T_NAME; }
.           return yytext[0];
%%