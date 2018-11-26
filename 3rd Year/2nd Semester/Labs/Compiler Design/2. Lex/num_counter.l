%{
#include<stdio.h>
int ints=0,floats=0,total=0;
%}

DIGIT    [0-9]

%%

{DIGIT}*        {ECHO;printf(" Integer");ints++;}
{DIGIT}*?\.{DIGIT}*    {ECHO;printf(" Float ");floats++;}

%%

main(void)
{
yylex();
total=ints+floats;
printf(" This File contains ...");
printf("\n\t%d integers", ints);
printf("\n\t%d floats", floats);
printf("\n\tIn total %d numbers.\n",total);
}
 
int yywrap()
{
return(1);
}
