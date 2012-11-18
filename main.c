/* 
 * File:   main.c
 * Author: connor
 *
 * Created on November 16, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "node.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
       char file_name[20];
      
       event_description *evt = calloc(1, sizeof(event_description));
       
       event_description * temp_event = evt;
       
       printf("\nEnter file name: ");
       scanf(" %19[a-zA-Z.]", file_name);
       
       FILE * file = fopen(file_name, "r");
       
       fscanf(file, " %[A-Za-z -]s", temp_event -> event_title);
       fscanf(file, " %[a-zA-Z0-9 ]s", temp_event -> event_date);
       fscanf(file, " %[0-9:]s", temp_event -> event_time);
       
       fclose(file);
       
       printf("\n%s\n%s\n%s\n ", temp_event->event_title, temp_event->event_date, temp_event->event_time);
       
      
       printf("\nEnter node file name: ");
       scanf(" %19[a-zA-Z.]", file_name);
       
       FILE * file_two = fopen(file_name, "r");
       
       
       if (file_two != NULL) {
           
          
           char temp_word[40];
           char temp_word2[40];
           int count = 0;

           
           while(!feof(file_two)) {
               
                fscanf(file_two, " %[0-9]s", temp_word);
                fscanf(file_two, " %[A-Za-z]s", temp_word2);
                
                printf("\nWord 1: %s", temp_word);
                printf("\nWord 2: %s", temp_word2);

           }
           
           fclose(file_two);
           
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
       
       countLines(file_name);

    return (EXIT_SUCCESS);
}

int countLines(char *file_name[20])
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
    }
        return 0;
}

