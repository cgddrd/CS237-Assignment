#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "course.h"

void loadCourses() {
    
       FILE * course_file = openFile("Enter courses file name:");
       
       if (course_file != NULL) {

           int count = 0;
           
           no_of_courses = countLines(course_file);
           
           rewind(course_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
           course_collection = calloc(1, no_of_courses * sizeof(event_course)); 
           
           while(!feof(course_file)) {

               
                fscanf(course_file, " %s", course_collection[count].id); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars.

                fscanf(course_file, " %d", &course_collection[count].course_length);
                
                
                course_collection[count].course_nodes = calloc(1, course_collection[count].course_length * sizeof(track_node));
                
                int i;
                
                int current_node;
                
                for (i = 0; i < course_collection[count].course_length; i++) {
                    
                fscanf(course_file, " %d", &current_node);
                    
                        int j = 0;
                        for (j=0; j < no_of_nodes; j++) {
               
                        //printf("\nNode %d: %d -> %s", i, node_collection[i].number, node_collection[i].type);
                        
                                if (current_node == node_collection[j].number) {

                                        course_collection[count].course_nodes[i] = &node_collection[j];
                            
                                 }
               
                        }
                    
                }

   
                count++;
               
           }
           
           fclose(course_file);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printCourses() 
{
         int i = 0;
         for (i=0; i < no_of_courses; i++) {
               
             printf("\nCourse %d: ID: %s, Length: %d", i, course_collection[i].id, course_collection[i].course_length);
             printf("\nNodes in course:");
             
             int j;
             for (j = 0; j < course_collection[i].course_length; j++) {
                
                  printf("\nNode %d: No: %d, ID: %s", j, course_collection[i].course_nodes[j]->number, course_collection[i].course_nodes[j]->type);
                 
                 
             }
             
             printf("\n\n");
           }
    
}


