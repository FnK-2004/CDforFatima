%{
int count = 0;
%}
%%
[AaeEiIoOuU] {printf("%s vowel\n", yytext);
       count++;}
.     {printf("%s consonant\n", yytext);}
\n    {return 0;}
%%

int yywrap(){}
int main(){
yylex();

return 0;
}