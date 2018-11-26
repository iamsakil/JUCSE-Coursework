%{
#include<stdio.h>
#include<stdlib.h>
void yyerror(char *s);
%}
%token NAME NUM
%%
statement: NAME'='expression
|expression{printf("\n%d\n",$1);};
expression:expression'+'NUM{$$=$1+$3;}
|expression'-'NUM{$$=$1-$3;}
|expression'/'NUM{$$=$1/$3;}
|expression'*'NUM{$$=$1*$3;}
|NUM{$$=$1;};
%%
int main()
{
while(yyparse());
}
yyerror(char *s)
{
fprintf(stdout,"\n%s",s);
}
