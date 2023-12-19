%{
int positiveIntCount = 0;
int negativeIntCount = 0;
int positiveFloatCount = 0;
int negativeFloatCount = 0;
%}
%%
[-+]?[0-9]+                  { if (atoi(yytext) > 0) positiveIntCount++; else if (atoi(yytext) < 0) negativeIntCount++; }
[-+]?[0-9]*\.[0-9]+          { if (atof(yytext) > 0) positiveFloatCount++; else if (atof(yytext) < 0) negativeFloatCount++; }
[^0-9\n]                     ; 
%%

int yywrap(){}
int main(){
yylex();
printf("Positive Integers: %d\nNegative Integers: %d\n", positiveIntCount, negativeIntCount);
printf("Positive Floating-point Numbers: %d\nNegative Floating-point Numbers: %d\n", positiveFloatCount, negativeFloatCount);
    
return 0;
}
