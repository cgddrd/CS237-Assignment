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
