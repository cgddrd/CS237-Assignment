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
           
         
           int lines = 0;
           int count = 0;
           
           lines = countLines(file_name);
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
           track_node *n = calloc(1, lines * sizeof(track_node)); 
           
           
           while(!feof(file_two)) {
               
               // track_node *evt2 = calloc(1, sizeof(track_node));
       
              //  track_node *temp_node = evt2;
               
                fscanf(file_two, " %d", &n[count].number); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars.
                
                //int temp_num = atoi(temp_word);
                
            //    temp_node->number = n[count].number;
                
                fscanf(file_two, " %[A-Za-z]s", n[count].type);
                
               // printf("\nWord 1: %d", temp_node->number);
                //printf("\nWord 2: %s", temp_node->type);
                
              //  n[count] = temp_node;
                        
                count++;
                
             //   free(evt2);

           }
           
           fclose(file_two);
           
           int i;
           
           for (i=0; i < lines; i++) {
               
             printf("\nNode %d: %d -> %s", i, n[i].number, n[i].type);  
               
           }
           
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
       
       //printf("\nPrick - %d", countLines(file_name));
       

    return (EXIT_SUCCESS);
}

int countLines(char *file_name) //Don't need a pointer 
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

