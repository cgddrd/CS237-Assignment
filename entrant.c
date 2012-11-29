#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "entrant.h"

void loadCompetitors() {
    
       FILE * entrant_file = openFile("Enter entrants file name:");
       
       if (entrant_file != NULL) {

           int count = 0;
           
           no_of_competitors = countLines(entrant_file);
           
           rewind(entrant_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
           competitor_collection = calloc(1, no_of_competitors * sizeof(competitor)); 
           
           while(!feof(entrant_file)) {

               
                fscanf(entrant_file, " %d", &competitor_collection[count].competitor_number); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars.

                fscanf(entrant_file, " %s", competitor_collection[count].course_id);
                
                int i;
                
                for (i = 0; i < no_of_courses; i++) {

                        
                                if (strcmp (competitor_collection[count].course_id, course_collection[i].id) == 0) {
                                                        
                                        competitor_collection[count].course = &course_collection[i];
                            
                                 }
               
                        }
                   
                        fscanf(entrant_file, " %[a-zA-Z ]s", competitor_collection[count].name);
                        
                        competitor_collection[count].current_checkpoint = NULL;
                        competitor_collection[count].current_progress = 0;
   
                count++;
               
           }
           
           fclose(entrant_file);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printCompetitors() 
{
         int i = 0;
         for (i=0; i < no_of_competitors; i++) {
               
             printf("\nCompetitor %d: No: %d, Name: %s, Course ID: %s", i, competitor_collection[i].competitor_number,
                     
                     competitor_collection[i].name, competitor_collection[i].course->id);  
               
           }
    
}

int checkNotStarted() {
 
    int i = 0;
    int count = 0;
    for (i=0; i < no_of_competitors; i++) {
        
        if(competitor_collection[i].current_checkpoint == NULL) {
            
            count++;
            
        }
             
     }
    
    return count;
    
}

int checkStarted() {
 
    int i = 0;
    int count = 0;
    for (i=0; i < no_of_competitors; i++) {
        
        if(competitor_collection[i].current_checkpoint != NULL) {
            
            count++;
            
        }
             
     }
    
    return count;   
}

void loadTimes() {
    
       FILE * time_file = openFile("Enter time file name:");
       
       if (time_file != NULL) {

           int node;
           int entrant_no;
           char time[5];
           char type [2];
           
           //no_of_competitors = countLines(entrant_file);
           
           //rewind(entrant_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
          // competitor_collection = calloc(1, no_of_competitors * sizeof(competitor)); 
           
           while(!feof(time_file)) {

                fscanf(time_file, " %s", type); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars
                fscanf(time_file, " %d", &node);
                
                fscanf(time_file, " %d", &entrant_no);

                fscanf(time_file, " %[0-9:]s", time);
                
                update(type, node, entrant_no, time);
                    
           }
           
           fclose(time_file);
           
           
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void updateEntrant(char * type, int node, int entrant, char * time) {
        
    int i;
         
    printf("\nwank");
    for (i = 0; i < no_of_competitors; i++) {
        
        if (competitor_collection[i].competitor_number == entrant) {
            
           // printf("\n BALH");
            
            int j;
            int test = 0;
            
            for (j = 0; j < competitor_collection[i].course->course_length; j++) {
                
                if (competitor_collection[i].course->course_nodes[j]->number == node && test != 1){
                    
                    track_node * temp = competitor_collection[i].course->course_nodes[j];
                    
                    competitor_collection[i].current_checkpoint = temp;
                    
                    printf("\nCompetitor %d -> Current Node: %d, %s", competitor_collection[i].competitor_number, 
                
                competitor_collection[i].current_checkpoint->number, competitor_collection[i].current_checkpoint->type); 
                    
                    strcpy(competitor_collection[i].time, time);
                    
                    test = 1;
                    
                }
                
            }
            
               
        }
       
           
    }
             
}

void update (char * type, int node, int entrant, char * time) {
    
    int i;
    int temp_bool = 0;
    
    for (i = 0; i < no_of_competitors; i++) {
        
       if (competitor_collection[i].competitor_number == entrant) {
           
           int j;
           
           for (j = 0; j < competitor_collection[i].course->course_length; j++) {
               
               if (competitor_collection[i].course->course_nodes[j]->number == node && temp_bool !=1) {
                   
                   if (j > (competitor_collection[i].current_progress - 1)) {
                       
                     track_node * temp = competitor_collection[i].course->course_nodes[j];
                    
                     competitor_collection[i].current_checkpoint = temp;  
                     
                     competitor_collection[i].current_progress = j + 1;
                     temp_bool = 1;
                     
                   }
               }
               
           }
           
       } 
        
        
    }
    
}


