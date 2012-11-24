#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "track.h"

void loadTracks() 
{
    
       FILE * track_file = openFile("Enter track file name:");
       
       if (track_file != NULL) {

           int count = 0;
           
           no_of_tracks = countLines(track_file);
           
           rewind(track_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
           track_collection = calloc(1, no_of_tracks * sizeof(course_track)); 
           
           while(!feof(track_file)) {
               
               int start_node = 0;
               int end_node = 0;
               
                fscanf(track_file, " %d", &track_collection[count].number); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars.

                fscanf(track_file, " %d", &start_node);
                 
                int i = 0;
                for (i=0; i < no_of_nodes; i++) {
               
                        //printf("\nNode %d: %d -> %s", i, node_collection[i].number, node_collection[i].type);
                        
                        if (start_node == node_collection[i].number) {
                            
                            track_node * arse = &node_collection[i];
                                                        
                            track_collection[count].start_node = arse;
                            
                        }
               
                }
                
                  fscanf(track_file, " %d", &end_node);
                 
                for (i=0; i < no_of_nodes; i++) {
               
                        //printf("\nNode %d: %d -> %s", i, node_collection[i].number, node_collection[i].type);
                        
                        if (end_node == node_collection[i].number) {
    
                            track_collection[count].end_node = &node_collection[i];
                            
                        }
               
                }
                  
                 fscanf(track_file, " %d", &track_collection[count].minutes);
   
                count++;
               
           }
           
           fclose(track_file);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printTracks() 
{
         int i = 0;
         for (i=0; i < no_of_tracks; i++) {
               
             printf("\nTrack %d: No: %d, SN: %d, EN: %d, Min: %d", i, track_collection[i].number, track_collection[i].start_node->number, 
                     
                     track_collection[i].end_node->number, track_collection[i].minutes);  
               
           }
    
}



