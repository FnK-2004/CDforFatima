#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool isPreprocessorDirective(const char *line){
return line[0]== '#';
}
int main(){
char inFile[100], oFile[100];
//C:\cplus\read.txt
	//C:\cplus\write.txt
printf("Enter the Name of the file to remove the preprocessor directive\n");
scanf(" %s", inFile);
printf("Enter the name of the Output file\n");
scanf(" %s", oFile);
FILE *inputFile=fopen(inFile, "r");
FILE *outputFile = fopen(oFile, "w");
if(inputFile==NULL || outputFile==NULL){
    perror("Error reading the file");
    return 1;
}
char line[1000];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        if (!isPreprocessorDirective(line)) {
            fputs(line, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    printf("Preprocessor directives discarded successfully!\n");
    return 0;
}
