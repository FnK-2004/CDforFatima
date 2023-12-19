#include <stdio.h>
void S(char **input);
void L(char **input);
void S(char **input) {
if (**input == '(') {
(*input)++;
L(input);
if (**input == ')') {
(*input)++;
} else {
printf("Error: Missing closing parenthesis\n");
return;
}
} else if (**input == 'a') {
(*input)++;
} else {
printf("Error: Invalid token '%c'\n", **input);
return;
}
}
void L(char **input) {
S(input);
if (**input == ',') {
(*input)++;
L(input);
}
}
int main() {
char input[100];
printf("Enter a string: ");
fgets(input, sizeof(input), stdin);
char *newline = strchr(input, '\n');
if (newline != NULL) {
*newline = '\0';
}
char *input_ptr = input;
S(&input_ptr);
if (*input_ptr == '\0') {
printf("String is valid\n");
} else {
printf("Error: Unexpected character at the end\n");
}
return 0;
}


