#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "track.h"

void loadTracks() 
{
    
       FILE * track_file = openFile("Enter track file name:");
       
       track_list = malloc(sizeof (list));
    
    track_list->head = NULL;
    track_list->tail = NULL;
       
       if (track_file != NULL) {

           int count = 0;
           int status = 0;

           
           while(!feof(track_file)) {
               
               linked_item * new_item = malloc(sizeof (linked_item));
               
               course_track * new_track = malloc(sizeof (course_track));
               
               new_item->next = NULL;
               
               int start_node = 0;
               int end_node = 0;
               
                status = fscanf(track_file, " %d", &new_track->number); /*& needed here when using scan because you need a pointer to the 
                                                                first element - not needed with string as it is an array of chars. */

                fscanf(track_file, " %d", &start_node);
                fscanf(track_file, " %d", &end_node);
                 
                int i = 0;
                
                linked_item * temp = node_list->head;
                
                while (temp !=NULL) {
                    
                    track_node * temp_node = (track_node *) temp->data;
                    
                    if (start_node == temp_node->number) {
                        
                      new_track->start_node = temp->data;  
                    }
                    
                    if (end_node == temp_node->number) {
                       
                        new_track->end_node = temp->data;
                        
                    }
                    
                    temp = temp->next;
                    
                }
                
         /*       for (i=0; i < no_of_nodes; i++) {
               
                        
                        if (start_node == node_collection[i].number) {
                            
                            track_node * temp_node = &node_collection[i];
                                                        
                            track_collection[count].start_node = temp_node;
                            
                          /*  temp_node->tracks_list 
                            
                        }
               
                } */
                
                  
                 
            /*    for (i=0; i < no_of_nodes; i++) {
               
                        /*printf("\nNode %d: %d -> %s", i, node_collection[i].number, node_collection[i].type); 
                        
                        if (end_node == node_collection[i].number) {
    
                            track_collection[count].end_node = &node_collection[i];
                            
                        }
               
                } */
                  
                 fscanf(track_file, " %d", &new_track->minutes);
                 
                 new_item->data = new_track;
                 
                if (status > 0) {

                if (track_list->head == NULL) {

                    track_list->head = new_item;
                    track_list->tail = new_item;

                } else {

                    linked_item * temp = track_list->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = new_item;
                    track_list->tail = new_item;
                }


            }
   
                count++;
               
           }
           
           fclose(track_file);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printTracks() 
{

          linked_item * temp_item = track_list->head;
    
    while (temp_item !=NULL) {
        
        course_track * temp_track = (course_track *) temp_item->data;
        
        printf("\nTrack No: %d, SN: %d, EN: %d, Min: %d", temp_track->number, temp_track->start_node->number, 
                     
                     temp_track->end_node->number, temp_track->minutes);  
        
        temp_item = temp_item->next;
        
    } 
    
}



