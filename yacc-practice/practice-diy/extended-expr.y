%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <math.h> 
    double symbtl[26];
    bool issym[26];

    extern int yylex(void);
    extern int yyerror(char * );
%}

%union {
    double rvalue;
    char lvalue;
}

%token<lvalue> T_NAME 
%token<rvalue> T_DOUBLE T_NUMBER T_EXP T_SQRT T_LOG

%type<rvalue> value;
%type<rvalue> expression;

%%
statement_list : statement '\n' statement_list   {printf("line\n");}
   | statement statement_list   {printf("line\n");}
   |                            {printf("empty\n");}
   ;    

statement: T_NAME '=' expression    {
                                        printf("Expression result %c = %lf\n", $1, $3); 
                                        issym[$1] = true; symbtl[$1] = $3;                                       
                                    }
   | expression                     {
                                        printf("Expression = %lf\n", $1);
                                    }
   ;

expression: value '+' expression    {$$ = $1 + $3;}
   | value '-' expression           {$$ = $1 - $3;}
   | value                          {$$ = $1;}
   | T_EXP '(' expression ')'       {$$ = exp($3);}
   | T_SQRT '(' expression ')'      {$$ = sqrt($3);}
   | T_LOG '(' expression ')'       {$$ = log($3);}
   ;

value: T_NUMBER {$$ = $1;}
    | T_DOUBLE  {$$ = $1;}
    | T_NAME    { 
                    if(issym[$1]){
                        $$ = symbtl[$1];
                    }
                    else {
                        fprintf(stderr, "variable does not have value\n");
                    }   
                }
    ;

%%

