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
        //C:\cplus\c files\L1E1nooflines.c
        //C:\cplus\write.txt

        printf("Enter the filename to open for writing: \n");  
		scanf("%s", filename);  
		fb = fopen(filename, "w+");   //comments
        if (fb == NULL){
        printf("Cannot open file \n");
        exit(0);
        }
        ca = getc(fa);
        while (ca != EOF){
            if(ca==' ')
			{
                putc(ca,fb);
            while(ca==' ')
                ca = getc(fa); 
			}
			putc(ca,fb);
			ca = getc(fa);
			}
			printf("Objective Achieved.");
			fclose(fa);
			fclose(fb);
			return 0;
}
