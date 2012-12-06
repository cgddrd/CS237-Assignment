#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "fileIO.h"

int loadNodes() {

    FILE * file_two = openFile("Enter node file name:");

    initialise(&node_list);

    int status = 0;

    if (file_two != NULL) {

        while (!feof(file_two)) {

            linked_node = malloc(sizeof (linked_item));
            linked_node->next = NULL;
            
            track_node * new_track = malloc(sizeof (track_node));

            status = fscanf(file_two, " %d %[a-zA-Z]s", &new_track->number, new_track->type);
            
            linked_node->data = new_track;

            if (status > 0) {

                addToList(&linked_node, &node_list);

            } else {
                
                free(linked_node);
                free(new_track);
            }
        }

        fclose(file_two);
        return 1;

    } else {
        return 0;
    }
}

void printNodes() {
    
    linked_item * temp = node_list->head;

    while (temp != NULL) {

        track_node * temp_node = (track_node *) temp->data;

        printf("Node: %d -> %s", temp_node->number, temp_node->type);

        temp = temp->next;

    }
}


