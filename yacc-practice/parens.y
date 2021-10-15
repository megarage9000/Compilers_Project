%%
TOP: S { printf("The last S = %d\n", $1); }
S: '(' S ')' { $$ = $2+1; printf("%d\n", $$); }
 | { $$ = 0; }
 ;
