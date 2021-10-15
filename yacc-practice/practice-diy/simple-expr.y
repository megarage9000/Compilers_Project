%{
    #include <stdio.h>
    extern int yylex(void);
    extern int yyerror(char * );
%}

%token NAME NUMBER NEWLINE END

%%
program: program line 
    | program END      {printf("EOF\n");}
    | line 
    ;

line: statement 
    | NEWLINE  
    ;

statement: NAME '=' expression { printf("Expression %c = %d\n", $1, $3); $$ = $3;} 
        | expression { printf("Expression result %d\n", $1); }
        ;

expression: expression '+' NUMBER { $$ = $1 + $3; }
        | expression '-' NUMBER { $$ = $1 - $3; }
        | NUMBER { $$ = $1; }
        ;
%%