%{
#include<stdio.h>
#include<stdlib.h>
%}

%token A B NL

%%
stmt: S NL {printf("\nValid string\n\n");
             exit(0);}
;
S: A S B |
;
%%

int yyerror(char *msg)
{
printf("\nInvalid string\n\n");
exit(0);
}

main()
{
printf("\nEnter the string: ");
yyparse();
}
