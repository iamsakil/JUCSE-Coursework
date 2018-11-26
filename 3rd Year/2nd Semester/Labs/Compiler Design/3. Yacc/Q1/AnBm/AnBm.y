%{
#include<stdio.h>
#include<stdlib.h>
%}
%token A B
%%
str: s '\n'    {  return 0;}
s : T U  ;
T: T A
| ;
U: B U
| ;
%%
main()
{
printf("\nEnter the String: ");  
yyparse();
printf("\nValid String.\n\n");
}
int yyerror()
{ 
  printf("\nInvalid String.\n\n");
 exit(0);
}
