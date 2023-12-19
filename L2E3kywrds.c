#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int main() {
    FILE *inputFile;
    char inputFileName[100];
    char word[100];
    int wordIndex = 0;
    bool insideWord = false;

    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Unable to open the input file.\n");
        return 1;
    }

    int c, i, j;
    //C:\cplus\read.txt
    while ((c = fgetc(inputFile)) != EOF) {
        if (isalnum(c)) {
            word[wordIndex++] = (char)c;
            insideWord = true;
        } else if (insideWord) {
            word[wordIndex] = '\0';
            for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
                if (strcmp(word, keywords[i]) == 0) {
                    
                    for (j = 0; word[j]; j++) {
                        word[j] = toupper(word[j]);
                    }
                    printf("%s\n", word);
                }
            }
            insideWord = false;
            wordIndex = 0;
        }
    }

    fclose(inputFile);

    return 0;
}
