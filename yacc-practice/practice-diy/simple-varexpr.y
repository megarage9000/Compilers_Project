%{
    #include <stdio.h>
    #include <stdbool.h>
    int symbtl[26];
    bool issym[26];

    extern int yylex(void);
    extern int yyerror(char * );
%}

%union {
    int rvalue;
    char lvalue;
}

%token<rvalue> NUMBER
%token<lvalue> NAME

%type<rvalue> expression
%type<rvalue> value

%%
program: statement program  
    |      
    ;

statement: NAME '=' expression { printf("Expression %c = %d\n", $1, $3); symbtl[$1] = $3; issym[$1] = true;} 
        | expression { printf("Expression result %d\n", $1); }
        ;

expression: expression '+' value { $$ = $1 + $3; }
        | expression '-' value { $$ = $1 - $3; }
        | value                { $$ = $1;}
        ;

value: NUMBER {$$ = $1;}
    | NAME {
            if(issym[$1]) {$$ = symbtl[$1];}
            else {fprintf(stderr, "Error!\n"); exit(0);}
            }
    ;

%%