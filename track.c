#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "track.h"

void loadTracks() 
{
    
       FILE * track_file = openFile("Enter track file name:");
       
       tracklist = malloc(sizeof (track_list));
    
    tracklist->head = NULL;
    tracklist->tail = NULL;
       
       if (track_file != NULL) {

           int count = 0;
           int status = 0;
           
           no_of_tracks = countLines(track_file);
           
           rewind(track_file); /*Resets the file pointer back to the beginning - could also use fseek(fp, 0) */
           
           /*dynamic allocation of array - same as: "track_node nodeArray[lines];" */
           track_collection = calloc(1, no_of_tracks * sizeof(course_track)); 
           
           while(!feof(track_file)) {
               
               linked_track * new_item = malloc(sizeof (linked_node));
               
               course_track * new_track = malloc(sizeof (course_track));
               
               new_item->next = NULL;
               
               int start_node = 0;
               int end_node = 0;
               
                status = fscanf(track_file, " %d", &new_track->number); /*& needed here when using scan because you need a pointer to the 
                                                                first element - not needed with string as it is an array of chars. */

                fscanf(track_file, " %d", &start_node);
                fscanf(track_file, " %d", &end_node);
                 
                int i = 0;
                
                linked_node * temp = nodelist->head;
                
                while (temp !=NULL) {
                    
                    if (start_node == temp->data->number) {
                        
                      new_track->start_node = temp->data;  
                    }
                    
                    if (end_node == temp->data->number) {
                       
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

                if (tracklist->head == NULL) {

                    tracklist->head = new_item;
                    tracklist->tail = new_item;

                } else {

                    linked_track * temp = tracklist->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = new_item;
                    tracklist->tail = new_item;
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

          linked_track * temp = tracklist->head;
    
    while (temp !=NULL) {
        
        printf("\nTrack No: %d, SN: %d, EN: %d, Min: %d", temp->data->number, temp->data->start_node->number, 
                     
                     temp->data->end_node->number, temp->data->minutes);  
        
        temp = temp->next;
        
    } 
    
}



