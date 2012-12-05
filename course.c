#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "course.h"

void loadCourses() {
    
       FILE * course_file = openFile("Enter courses file name:");
       
        course_list = malloc(sizeof (list));
   
    course_list->head = NULL;
    course_list->tail = NULL;
       
       if (course_file != NULL) {

           int count = 0;
           int status = 0;

           
           while(!feof(course_file)) {

               linked_course = malloc(sizeof (linked_item));
               
               event_course * new_course = malloc(sizeof (event_course));
               
               linked_course->next = NULL;
               
                status = fscanf(course_file, " %c", &new_course->id); 

                fscanf(course_file, " %d", &new_course->course_length);
                
                
                new_course->course_nodes = calloc(1, new_course->course_length * sizeof(track_node));
                
                int i;
                
                int current_node;
                
                for (i = 0; i < new_course->course_length; i++) {
                    
                fscanf(course_file, " %d", &current_node);
                
                linked_item * temp = node_list->head;
                
                while (temp !=NULL){
                    
                    track_node * temp_node = (track_node *) temp->data;
                    
                    if (current_node == temp_node->number) {

                              new_course->course_nodes[i] = temp_node;
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
                
                linked_course->data = new_course;
                
                if (status > 0) {

                if (course_list->head == NULL) {

                    course_list->head = linked_course;
                    course_list->tail = linked_course;

                } else {

                    linked_item * temp = course_list->tail;
                   

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = linked_course;
                    course_list->tail = linked_course;
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
   
    linked_item * temp = course_list->head;
    
    while (temp !=NULL) {
        
        event_course * temp_event = (event_course *) temp->data;
        
        printf("\nCourse ID: %c, Length: %d",temp_event->id, temp_event->course_length);
             printf("\nNodes in course:");
             
             int i;
             for (i = 0; i < temp_event->course_length; i++) {
                
                  printf("\nNode %d: No: %d, ID: %s", i, temp_event->course_nodes[i]->number, temp_event->course_nodes[i]->type);
                 
                 
             }
             
             printf("\n\n");
        
        temp = temp->next;
        
    } 
    
}


