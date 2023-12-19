%{
int wordCount = 0;
int charCount = 0;
int blankCount = 0;
int lineCount = 0;
%}
%%
[a-zA-Y]+   { wordCount++; charCount += yyleng; }
" "         { blankCount++; charCount++; }
\n          { lineCount++; charCount++; }
.           { charCount++; }
%%

int yywrap(){}
int main(){
yylex();
printf("Word count: %d\n", wordCount);
    printf("Character count: %d\n", charCount);
    printf("Blank count: %d\n", blankCount);
    printf("Line count: %d\n", lineCount);
return 0;
}