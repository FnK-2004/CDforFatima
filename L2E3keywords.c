#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
	char keywords[33][9] = {"auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"};
	char c[100];
    FILE *if1; 
	char filename[100], ca, word[100], found;
    printf("Enter the Name of the file\n");
	scanf(" %s", filename);
    if1 = fopen(filename, "r");
    //C:\cplus\read.txt
    if (if1 == NULL) 
	{
        printf("Error opening input file");
        return 1;
    }
    ca=getc(if1);
    while (ca != EOF) {
    	int i=0;
    	memset(word, '\0', sizeof(word));
        while(isalpha(ca)!=0)
        {
        	word[i]=ca;
        	i=i+1;
        	ca=getc(if1);
		}
		for(i=0; i<32; i++)
		{
			char f[100];
			strcpy(f, keywords[i]);
	        if(strcmp(f, word)!=0)
	        {
	            found = 1;
	            printf("%s\n", keywords[i]);
	            break;
	        }
		}
		ca=getc(if1);
    }
    fclose(if1);
    return 0;
}
