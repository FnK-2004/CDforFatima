#include <stdlib.h>
#include <stdio.h>
int main(){
    char filename[100];
    FILE *fa, *fb;
    int ca, cb;
        printf("Enter the filename to open for reading: \n");  
	scanf("%s", filename);  
	fa = fopen(filename, "r");  
	if (fa == NULL){
	        printf("Cannot open file \n");
	        exit(0);
	        }
    printf("Enter the filename to open for writing: \n");  
		scanf("%s", filename);  
		fb = fopen(filename, "w+");
    ca = getc(fa);
    while (ca != EOF){
            cb = getc(fa);
			if (cb == '#')
			{
				while(ca != '\n')
					ca = getc(fa);
			}
		else
			putc(ca,fb);
		ca = getc(fa);
		}
	fclose(fa);
	fclose(fb);
	return 0;//u
}
