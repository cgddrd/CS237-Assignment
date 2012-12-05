#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "fileIO.h"

void loadNodes() 
{
    
       FILE * file_two = openFile("Enter node file name:");
       
       node_list = malloc(sizeof (list));
    
    node_list->head = NULL;
    node_list->tail = NULL;
       
    int status = 0;
       
       if (file_two != NULL) {
           
           int count = 0;

           while(!feof(file_two)) { 
               
               linked_node = malloc(sizeof (linked_item));
               
               track_node * new_track = malloc(sizeof (track_node));
               
               linked_node->next = NULL;
               
                /*fscanf(file_two, " %d", &node_collection[count].number); 
                fscanf(file_two, " %[A-Za-z]s", node_collection[count].type); */
               
               status = fscanf(file_two, " %d", &new_track->number); 
               
               fscanf(file_two, " %[A-Za-z]s", new_track->type);
   
                count++;
                
                linked_node->data = new_track;
                
                if (status > 0) {

                if (node_list->head == NULL) {

                    node_list->head = linked_node;
                    node_list->tail = linked_node;

                } else {

                    linked_item * temp = node_list->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = linked_node;
                    node_list->tail = linked_node;
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
   linked_item * temp = node_list->head;
    
    while (temp !=NULL) {
        
        track_node * temp_node = (track_node *) temp->data;
        
        printf("Node: %d -> %s", temp_node->number, temp_node->type);
        
        temp = temp->next;
        
    } 
}


