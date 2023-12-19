#include <stdio.h>
void S(char **input);
void T(char **input);
void S(char **input) {
if (**input == 'a' || **input == '>' || **input == '(') {
(*input)++;
} else {
printf("Error: Invalid token '%c'\n", **input);
return;
}
}
void T(char **input) {
while (**input == ',') {
(*input)++;
S(input);
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
char *input_ptr = input; // Create a pointer to the input string
S(&input_ptr);
if (*input_ptr == '\0') {
printf("String is valid\n");
} else {
printf("Error: Unexpected character at the end\n");
}
return 0;
}
