%{
int scanfCount = 0;
int printfCount = 0;
%}
%%
"scanf"     { scanfCount++; printf("READ"); }
"printf"    { printfCount++; printf("WRITE"); }
.|\n        { putchar(yytext[0]); }
%%

int yywrap(){}
int main(){
yylex();
FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }

    yyin = inputFile;
    yylex();

    fclose(inputFile);

    fprintf(stderr, "Number of scanf: %d\nNumber of printf: %d\n", scanfCount, printfCount);
    
return 0;
}
