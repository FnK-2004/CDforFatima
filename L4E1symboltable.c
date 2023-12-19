#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKEN_LENGTH 100
#define MAX_SYMBOLS 1000
enum TokenType {
    KEYWORD,
    ARITHMETIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR,
    SPECIAL_SYMBOL,
    NUMERICAL_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER
};
struct Token {
    enum TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
    int row;
    int col;
};
int i;
struct Token localSymbolTable[MAX_SYMBOLS];
int localSymbolCount = 0;
bool isKeyword(char* str) {
    char* keywords[] = {"if", "else", "while", "int", "char", "return"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}
bool isSpecialSymbol(char c) {
    char specialSymbols[] = "+-*/<>=!&|(),;{}[]";
    return strchr(specialSymbols, c) != NULL;
}
bool isComment(FILE* file) {
    int c = fgetc(file);
    if (c == '/') {
        int nextChar = fgetc(file);
        if (nextChar == '/') {
            while ((c = fgetc(file)) != EOF && c != '\n');
            return true;
        } else if (nextChar == '*') {
            int prevChar = ' ';
            while ((c = fgetc(file)) != EOF) {
                if (prevChar == '*' && c == '/') {
                    return true;
                }
                prevChar = c;
            }
        } else {
            ungetc(nextChar, file);
        }
    } else {
        ungetc(c, file);
    }
    return false;
}
void skipWhitespace(FILE* file) {
    int c;
    while ((c = fgetc(file)) != EOF && isspace(c));
    ungetc(c, file);
}
struct Token getNextToken(FILE* file) {
    struct Token token;
    int c;
    int row = 1, col = 0;
    skipWhitespace(file);
    while ((c = fgetc(file)) != EOF) {
        col++;
        if (c == '\n') {
            row++;
            col = 0;
        }
        if (isComment(file)) {
            continue;
        }
        if (c == '"') {
            token.type = STRING_LITERAL;
            token.row = row;
            token.col = col - 1;
            int i = 0;
            while ((c = fgetc(file)) != EOF && c != '"') {
                token.lexeme[i++] = c;
                col++;
            }
            token.lexeme[i] = '\0';
            return token;
        }
        if (isalpha(c) || c == '_') {
            token.lexeme[0] = c;
            int i = 1;
            while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
                token.lexeme[i++] = c;
                col++;
            }
            token.lexeme[i] = '\0';
            if (isKeyword(token.lexeme)) {
                token.type = KEYWORD;
            } else {
                token.type = IDENTIFIER;
            }
            token.row = row;
            token.col = col - i;
            ungetc(c, file);
            return token;
        }
        if (isdigit(c)) {
            token.lexeme[0] = c;
            int i = 1;
            while ((c = fgetc(file)) != EOF && (isdigit(c) || c == '.')) {
                token.lexeme[i++] = c;
                col++;
            }
            token.lexeme[i] = '\0';
            token.type = NUMERICAL_CONSTANT;
            token.row = row;
            token.col = col - i;
            ungetc(c, file);
            return token;
        }
        if (isSpecialSymbol(c)) {
            token.lexeme[0] = c;
            int i = 1;
            while ((c = fgetc(file)) != EOF && isSpecialSymbol(c)) {
                token.lexeme[i++] = c;
                col++;
            }
            token.lexeme[i] = '\0';
            token.type = SPECIAL_SYMBOL;
            token.row = row;
            token.col = col - i;
            ungetc(c, file);
            return token;
        }
    }
    token.type = EOF;
    token.lexeme[0] = '\0';
    token.row = row;
    token.col = col;
    return token;
}
int main() {
    FILE* file;
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    //C:\cplus\read.txt
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }
    struct Token token;
    while ((token = getNextToken(file)).type != EOF) {
        if (token.type == IDENTIFIER) {
            localSymbolTable[localSymbolCount++] = token;
        }
        printf("Row %d, Col %d: Type: %d, Lexeme: %s\n", token.row, token.col, token.type, token.lexeme);
    }
    fclose(file);
    return 0;
}
