#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKEN_LENGTH 100

enum TokenType {
    KEYWORD,
    ARITHMETIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR,
    OPERATOR,
    NUMERICAL_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER
};

bool isKeyword(char* str) { int i;
    char* keywords[] = {"if", "else", "while", "int", "char", "return"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

void printToken(int line, int column, char* lexeme, enum TokenType type) {
    char* typeStr;
    switch (type) {
        case KEYWORD:
            typeStr = "Keyword";
            break;
        case ARITHMETIC_OPERATOR:
            typeStr = "Arithmetic Operator";
            break;
        case RELATIONAL_OPERATOR:
            typeStr = "Relational Operator";
            break;
        case LOGICAL_OPERATOR:
            typeStr = "Logical Operator";
            break;
 c       case OPERATOR:
            typeStr = "Operator";
            break;
        case NUMERICAL_CONSTANT:
            typeStr = "Numerical Constant";
            break;
        case STRING_LITERAL:
            typeStr = "String Literal";
            break;
        case IDENTIFIER:
            typeStr = "Identifier";
            break;
        default:
            typeStr = "Unknown";
            break;
    }
    if(column<0)
    {
    	column=column*-1;
	}
    printf("Line %d, Column %d: %s - %s\n", line, column, lexeme, typeStr);
}
void tokenizeCCode(FILE* file) {
    int c;
    int line = 1;
    int column = 0;
    char lexeme[MAX_TOKEN_LENGTH];
    int lexemeLength = 0;
    enum TokenType currentTokenType = IDENTIFIER;
    while ((c = fgetc(file)) != EOF) {
        column++;
        if (c == '\n') {
            line++;
            column = 0;
        }
        if (c == '/') {
            int nextChar = fgetc(file);
            column++;
            if (nextChar == '/') {
                while ((c = fgetc(file)) != EOF && c != '\n') {
                    column++;
                }
                if (c == '\n') {
                    line++;
                    column = 0;
                }
                continue;
            } else if (nextChar == '*') {
                int prevChar = ' ';
                while ((c = fgetc(file)) != EOF) {
                    column++;
                    if (prevChar == '*' && c == '/') {
                        break;
                    }
                    prevChar = c;
                    if (c == '\n') {
                        line++;
                        column = 0;
                    }
                }
                continue;
            } else {
                ungetc(nextChar, file);
                c = '/';
                column--;
            }
        }
        // ppd
        if (c == '#') {
            while ((c = fgetc(file)) != EOF && c != '\n') {
                column++;
            }
            if (c == '\n') {
                line++;
                column = 0;
            }
            continue;
        }
        if (c == '"') {
            lexeme[lexemeLength++] = '"';
            while ((c = fgetc(file)) != EOF) {
                lexeme[lexemeLength++] = c;
                if (c == '"') {
                    break;
                }
                if (c == '\n') {
                    line++;
                    column = 0;
                }
            }
            lexeme[lexemeLength] = '\0';
            printToken(line, column - lexemeLength, lexeme, STRING_LITERAL);
            lexemeLength = 0;
            continue;
        }
		if (isalpha(c) || c == '_') {
            lexeme[lexemeLength++] = c;
            while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
                lexeme[lexemeLength++] = c;
            }
            lexeme[lexemeLength] = '\0';
            currentTokenType = isKeyword(lexeme) ? KEYWORD : IDENTIFIER;
            printToken(line, column - lexemeLength, lexeme, currentTokenType);
            lexemeLength = 0;
            ungetc(c, file);
            continue;
        }
        if (isdigit(c)) {
            lexeme[lexemeLength++] = c;
            while ((c = fgetc(file)) != EOF && (isdigit(c) || c == '.')) {
                lexeme[lexemeLength++] = c;
            }
            lexeme[lexemeLength] = '\0';
            printToken(line, column - lexemeLength, lexeme, NUMERICAL_CONSTANT);
            lexemeLength = 0;
            ungetc(c, file);
            continue;
        }
        if (strchr("+-*/<>=!&|(),;{}[]", c)) {
            lexeme[lexemeLength++] = c;
            lexeme[lexemeLength] = '\0';
            printToken(line, column - lexemeLength, lexeme, OPERATOR);
            lexemeLength = 0;
            continue;
        }
    }
}
int main() {
    FILE* file; char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    //C:\cplus\read.txt
    if (file == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }
    tokenizeCCode(file);
    fclose(file);
    return 0;
}
