#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "track.h"

int loadTracks() {

    FILE * track_file = openFile("Enter track file name:");

    initialise(&track_list);

    if (track_file != NULL) {

        int status = 0;

        while (!feof(track_file)) {

            linked_track = malloc(sizeof(linked_item));
            course_track * new_track = malloc(sizeof(course_track));

            linked_track->next = NULL;

            int start_node = 0;
            int end_node = 0;

            status = fscanf(track_file, " %d%d%d%d", &new_track->number, &start_node, &end_node, &new_track->minutes);

            locateNodes(new_track, start_node, end_node);

            linked_track->data = new_track;

            if (status > 0) {

                addToList(&linked_track, &track_list);

            } else {
                
                free(linked_track);
                free(new_track);
            }
        }

        fclose(track_file);
        return 1;

    } else {
        return 0;
    }
}

void locateNodes(course_track * new_track, int start_node, int end_node) {

    linked_item * temp = node_list->head;

    while (temp != NULL) {

        course_node * temp_node = (course_node *) temp->data;

        if (start_node == temp_node->number) {

            new_track->start_node = temp->data;
        }

        if (end_node == temp_node->number) {

            new_track->end_node = temp->data;

        }
        
        temp = temp->next;
    }
}

void printTracks() {

    linked_item * temp_item = track_list->head;

    while (temp_item != NULL) {

        course_track * temp_track = (course_track *) temp_item->data;

        printf("\nTrack No: %d, SN: %d, EN: %d, Min: %d", temp_track->number, temp_track->start_node->number,

                temp_track->end_node->number, temp_track->minutes);

        temp_item = temp_item->next;

    }

}



