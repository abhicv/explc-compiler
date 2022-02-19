%{
    #include <stdio.h> 
	#include "y.tab.h"
%}

%%

[a-zA-Z0-9]	{
        yylval.charVal = *yytext;
        return CHARACTER;
}
[+|-|*|/]   { 
        yylval.charVal = *yytext;
        return *yytext;
}
[()]    return *yytext;
.	    return *yytext;
[\n]    return *yytext;

%%

int yywrap()
{
	return 1;
}