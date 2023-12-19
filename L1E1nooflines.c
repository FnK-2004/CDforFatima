#include <stdio.h>
#define MAX_FILE_NAME 100
int main()
{
    FILE *fp;
    int count = 1; // Line counter (result)
    int characters = 0;
    char filename[MAX_FILE_NAME];
    char c; // To store a character read from file

    // Get file name from user. The file should be
    // either in current folder or complete path should be provided
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open the file
    fp = fopen(filename, "r");
    printf(fp);
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
        else {
            characters=characters+1;
        }

    // Close the file
    fclose(fp);
    printf("The file %s has %d lines\n ", filename, count);
    printf("Total number of characters : %d\n",characters);
    return 0;
}

