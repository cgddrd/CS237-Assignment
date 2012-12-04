#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "course.h"

void loadCourses() {
    
       FILE * course_file = openFile("Enter courses file name:");
       
        courselist = malloc(sizeof (course_list));
    
    courselist->head = NULL;
    courselist->tail = NULL;
       
       if (course_file != NULL) {

           int count = 0;
           int status = 0;
           
           no_of_courses = countLines(course_file);
           
           rewind(course_file); 
           
           course_collection = calloc(1, no_of_courses * sizeof(event_course)); 
           
           while(!feof(course_file)) {

               linked_course * new_item = malloc(sizeof (linked_course));
               
               event_course * new_course = malloc(sizeof (event_course));
               
               new_item->next = NULL;
               
                status = fscanf(course_file, " %c", &new_course->id); 

                fscanf(course_file, " %d", &new_course->course_length);
                
                
                new_course->course_nodes = calloc(1, new_course->course_length * sizeof(track_node));
                
                int i;
                
                int current_node;
                
                for (i = 0; i < new_course->course_length; i++) {
                    
                fscanf(course_file, " %d", &current_node);
                
                linked_node * temp = nodelist->head;
                
                while (temp !=NULL){
                    
                    if (current_node == temp->data->number) {

                              new_course->course_nodes[i] = temp->data;
                              printf("\nWANK: %c, %d", new_course->id, new_course->course_nodes[i]->number);
                            
                                 }
                    
                    temp = temp->next;
                    
                }
                
                    
                   /*     int j = 0;
                        for (j=0; j < no_of_nodes; j++) {
               
                        
                                if (current_node == node_collection[j].number) {

                                        course_collection[count].course_nodes[i] = &node_collection[j];
                            
                                 }
               
                        } */
                    
                }
                
                new_item->data = new_course;
                
                if (status > 0) {

                if (courselist->head == NULL) {

                    courselist->head = new_item;
                    courselist->tail = new_item;

                } else {

                    linked_course * temp = courselist->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = new_item;
                    courselist->tail = new_item;
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
   
    linked_course * temp = courselist->head;
    
    while (temp !=NULL) {
        
        printf("\nCourse ID: %c, Length: %d", temp->data->id, temp->data->course_length);
             printf("\nNodes in course:");
             
             int i;
             for (i = 0; i < temp->data->course_length; i++) {
                
                  printf("\nNode %d: No: %d, ID: %s", i, temp->data->course_nodes[i]->number, temp->data->course_nodes[i]->type);
                 
                 
             }
             
             printf("\n\n");
        
        temp = temp->next;
        
    } 
    
}


