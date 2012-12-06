#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"

void initialise(list ** data_list) {
    
   (*data_list) = malloc(sizeof (list));
   
   
  
    (*data_list)->head = NULL;
    (*data_list)->tail = NULL;

}

int addToList(linked_item ** new_item, list ** data_list) {
    
    
 

                if ((*data_list)->head == NULL) {

                    (*data_list)->head = (*new_item);
                    (*data_list)->tail = (*new_item);

                } else {

                    linked_item * temp = (*data_list)->tail;

                    temp->next = (*new_item);
                    (*data_list)->tail = (*new_item);
                }
            
    
}

int countLines(FILE * file) 
{
    FILE * fp;
    int countLines = 0;
    int i;


    fp = file;
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

FILE * openFile(char * prompt)
{
    
    char file_name[101];
    
    printf("\n%s ", prompt);
    scanf(" %100[a-zA-Z0-9._]", file_name);
    
    FILE * file = fopen(file_name, "r");
    
    return file;
    
}