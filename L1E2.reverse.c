#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> // For exit() 
int main()
{
	FILE *fptr1, *fptr2;  
	char filename[100], c;
	char string[100]; int i=0;
	//C:\cplus\read.txt
	//C:\cplus\write.txt
	printf("Enter the filename to open for reading: \n");  
	scanf("%s", filename);  
	fptr1 = fopen(filename, "r");  
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	printf("Enter the filename to open for writing: \n");  
	scanf("%s", filename); 	 
	fptr2 = fopen(filename, "w+");
	c = fgetc(fptr1);
	while (c != EOF)
	{
		string[i]=c;
		c = fgetc(fptr1);
		i=i+1;
	}
	printf("\nContents of file 1: %s", string);
	strrev(string);
	printf("\nContents of file 1 reversed: %s", string);
	i=0;
	while (i <= strlen(string))
	{
		fputc(string[i], fptr2);
		i=i+1;
	}
	fclose(fptr2);
	fptr2 = fopen(filename, "r");
	c = fgetc(fptr2);
	printf("\nContents of file 2: ");
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fptr2);
	}
    long size; FILE *fp;
    fclose(fptr2);
    fp = fopen(filename, "rb");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    printf("\nThe size of the file = %ld bytes.\n", size);
	fclose(fptr1);
	fclose(fptr2);
	return 0; 
}
