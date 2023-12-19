%{
#include <stdio.h>

int insideComment = 0;
%}

%x COMMENT

%%
"/*"                { BEGIN(COMMENT); insideComment = 1; }
<COMMENT>"*/"       { BEGIN(INITIAL); insideComment = 0; }
<COMMENT>.          ; /* Ignore characters inside comments */

[A-Z]               { if (!insideComment) printf("%c", yytext[0] + 32); }
.|\n               { if (!insideComment) printf("%s", yytext); }
%%

int yywrap(){}


int main() {
    yylex();
    return 0;
}
