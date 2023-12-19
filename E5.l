%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%X\n", atoi(yytext)); }
.|\n      ;
%%

int yywrap(){}


int main() {
    printf("Enter a decimal number: ");
    yylex();
    return 0;
}
