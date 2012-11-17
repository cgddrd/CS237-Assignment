/* 
 * File:   main.c
 * Author: connor
 *
 * Created on November 16, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

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
           
          // while (fscanf(file, "   %s   ", &etc) != EOF)
           
           char temp_word[40];
           int count = 0;
           
           while(!feof(file_two)) {
               
                fscanf(file_two, " %[a-zA-Z0-9]s", temp_word);
                
                count++;
                
                printf("\nNumber: %d - %s", count, temp_word);

           }
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
       
    return (EXIT_SUCCESS);
}

