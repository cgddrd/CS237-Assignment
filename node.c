#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "fileIO.h"

void loadNodes() 
{
    
       FILE * file_two = openFile("Enter node file name:");
       
       nodelist = malloc(sizeof (node_list));
    
    nodelist->head = NULL;
    nodelist->tail = NULL;
       
    int status = 0;
       
       if (file_two != NULL) {
           
           int count = 0;
           
           no_of_nodes = countLines(file_two);
           
           rewind(file_two); 
           
           node_collection = calloc(1, no_of_nodes * sizeof(track_node)); 
           
           while(!feof(file_two)) { 
               
               linked_node * new_node = malloc(sizeof (linked_node));
               
               track_node * new_track = malloc(sizeof (track_node));
               
               new_node->next = NULL;
               
                /*fscanf(file_two, " %d", &node_collection[count].number); 
                fscanf(file_two, " %[A-Za-z]s", node_collection[count].type); */
               
               status = fscanf(file_two, " %d", &new_track->number); 
               
               fscanf(file_two, " %[A-Za-z]s", new_track->type);
   
                count++;
                
                new_node->data = new_track;
                
                if (status > 0) {

                if (nodelist->head == NULL) {

                    nodelist->head = new_node;
                    nodelist->tail = new_node;

                } else {

                    linked_node * temp = nodelist->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = new_node;
                    nodelist->tail = new_node;
                }


            }
               
           }
           
           fclose(file_two);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printNodes() 
{
   linked_node * temp = nodelist->head;
    
    while (temp !=NULL) {
        
        printf("Node: %d -> %s", temp->data->number, temp->data->type);
        
        temp = temp->next;
        
    } 
}


