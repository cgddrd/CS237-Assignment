#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"


int countLines(char *file_name) 
{
    FILE * fp;
    int countLines = 0;
    int i;


    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("We can't open the file.");
        fclose(fp);
        return 1;
    }
    else
    {
        while((i=fgetc(fp))!=EOF)
        {
            if (i == '\n')
                countLines++;
        }

        printf("\nNumber of lines: %d\n",countLines);
        return countLines;
    }
}

FILE * openFile()
{
    
    char file_name[40];
    
    printf("\nEnter file name: ");
    scanf(" %19[a-zA-Z.]", file_name);
    
    FILE * file = fopen(file_name, "r");
    
    return file;
    
    
}