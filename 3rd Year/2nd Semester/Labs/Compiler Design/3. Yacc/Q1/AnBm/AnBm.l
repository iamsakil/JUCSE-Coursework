%{
#include "y.tab.h"
%}
%%
[aA] {return A;}
[bB] {return B;}
\n {return yytext[0];}
. {return yytext[0];}
%%
yywrap()
{}
