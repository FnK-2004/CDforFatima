#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    SYMBOL,
    NUMBER,
    ERROR
};

struct Token {
    enum TokenType type;
    char lexeme[50];
    int line;
    int column;
};

void printToken(struct Token token) {
    const char* typeStr;

    switch (token.type) {
        case KEYWORD:
            typeStr = "KEYWORD";
            break;
        case IDENTIFIER:
            typeStr = "IDENTIFIER";
            break;
        case SYMBOL:
            typeStr = "SYMBOL";
            break;
        case NUMBER:
            typeStr = "NUMBER";
            break;
        default:
            typeStr = "ERROR";
    }

    printf("Token: %s (%s) at Line %d, Column %d\n", typeStr, token.lexeme, token.line, token.column);
}

// Function to check if a string is a keyword
int isKeyword(const char* str) {
    // List of keywords
    const char* keywords[] = {"void", "main", "if"};
    int i;
    for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;  // It's a keyword
        }
    }

    return 0;  // Not a keyword
}

void tokenize(const char* code) {
    int i = 0;
    int len = strlen(code);
    int line = 1;
    int column = 1;

    while (i < len) {
        struct Token token;
        token.lexeme[0] = '\0';
        token.line = line;
        token.column = column;

        while (i < len && isspace(code[i])) {
            if (code[i] == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            i++;
        }

        // Check for keywords or identifiers
        if (isalpha(code[i])) {
            int j = 0;
            while (i < len && (isalnum(code[i]) || code[i] == '_')) {
                token.lexeme[j++] = tolower(code[i++]);  // Convert to lowercase for case-insensitivity
            }
            token.lexeme[j] = '\0';
            token.type = isKeyword(token.lexeme) ? KEYWORD : IDENTIFIER;
            printToken(token);
        }

        // Check for symbols
        else if (strchr("(){};=", code[i]) != NULL) {
            token.lexeme[0] = code[i++];
            token.lexeme[1] = '\0';
            token.type = SYMBOL;
            printToken(token);
        }

        // Check for numbers
        else if (isdigit(code[i])) {
            int j = 0;
            while (i < len && isdigit(code[i])) {
                token.lexeme[j++] = code[i++];
            }
            token.lexeme[j] = '\0';
            token.type = NUMBER;
            printToken(token);
        }

        // Error: unrecognized character
        else {
            token.lexeme[0] = code[i++];
            token.lexeme[1] = '\0';
            token.type = ERROR;
            printToken(token);
        }
    }
}

int main() {
    const char* code = "Void main() {\n    if (a > b)\n        a = 5;\n}";

    tokenize(code);

    return 0;
}
