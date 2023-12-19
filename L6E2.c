#include <stdio.h>
void S(char **input);
void U(char **input);
void V(char **input);
void W(char **input);
void S(char **input) {
U(input);
V(input);
W(input);
}
void U(char **input) {
if (**input == '(') {
(*input)++;
S(input);
if (**input == ')') {
(*input)++;
} else {
printf("Error: Missing closing parenthesis\n");
return;
}
} else if (**input == 'a') {
(*input)++;
S(input);
if (**input == 'b') {
(*input)++;
} else {
printf("Error: Expected 'b' after 'aS'\n");
return;
}
} else if (**input == 'd') {
(*input)++;
} else {
printf("Error: Invalid token '%c'\n", **input);
return;
}
}
void V(char **input) {
if (**input == 'a') {
(*input)++;
V(input);
}
}
void W(char **input) {
if (**input == 'c') {
(*input)++;
W(input);
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


