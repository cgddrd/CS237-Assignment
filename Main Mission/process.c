#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

int loadTimes() {

    FILE * time_file = openFile("Enter time file name:");

    if (time_file != NULL) {

        int node;
        int entrant_no;
        char time[5];
        char type;
        int status;

        while (!feof(time_file)) {

            status = fscanf(time_file, " %c%d%d%s", &type, &node, &entrant_no, time);

            if (status > 0) {
                updateEntrant(entrant_list->head, type, node, entrant_no, time);
            }
        }

        fclose(time_file);
        return 1;

    } else {

        return 0;

    }
}

void updateEntrant(linked_item * current, char type, int node, int entrant, char * time) {

    competitor * temp_competitor = (competitor *) current->item_data;

    int temp_bool = 0;

    if (temp_competitor->competitor_number == entrant) {

        int j;

        for (j = 0; j < temp_competitor->course->course_length; j++) {

            if (temp_competitor->course->course_nodes[j]->number == node && temp_bool != 1) {

                if (j > (temp_competitor->current_progress - 1)) {

                    course_node * temp = temp_competitor->course->course_nodes[j];

                    if (strcmp(temp_competitor->course->course_nodes[j]->type, "CP") == 0) {

                        temp_competitor->current_status = 1;

                    } else if (strcmp(temp_competitor->course->course_nodes[j]->type, "JN") == 0) {

                        temp_competitor->current_status = 2;

                    }

                    temp_competitor->last_logged_node = temp;
                    temp_competitor->current_progress = j + 1;
                    temp_competitor->last_logged_node_index = j;
                    strcpy(temp_competitor->last_logged_time, time);

                    if (temp_competitor->current_progress == 1) {

                        strcpy(temp_competitor->start_time, time);
                    }

                    convertTime(temp_competitor, time);

                    temp_bool = 1;

                    if (temp_competitor->current_progress == temp_competitor->course->course_length) {

                        temp_competitor->current_status = 4;

                        strcpy(temp_competitor->finish_time, time);
                    }

                    updateOtherEntrants(entrant_list->head, current, time);
                }
            }
        }

    } else {

        if (current->next != NULL) {

            updateEntrant(current->next, type, node, entrant, time);

        } else {

            printf("\n\nEntrant cannot be located. Please try again.");
        }
    }
}

void convertTime(competitor * new_competitor, char * time_string) {

    char *hours = (char*) malloc(2);
    char *mins = (char*) malloc(2);

    strncpy(hours, time_string, 2);

    strncpy(mins, time_string + 3, 5);

    new_competitor->last_cp_time.hour = atoi(hours);

    new_competitor->last_cp_time.minutes = atoi(mins);

}

void updateOtherEntrants(linked_item * current, linked_item * new, char * time) {

    competitor * current_competitor = (competitor *) current->item_data;
    competitor * new_competitor = (competitor *) new->item_data;

    if (current_competitor->competitor_number != new_competitor->competitor_number) {

        if (strcmp(current_competitor->last_logged_time, time) != 0) {

            if (current_competitor->current_status == 1 || current_competitor->current_status == 2) {

                updateCurrentEntrantTrack(current_competitor);

                current_competitor->current_status = 3;

            } else if (current_competitor->current_status == 3) {

                if (checkEntrantCompletedTrack(current_competitor, new_competitor)) {

                    int next_node_index = (current_competitor->last_logged_node_index) + 1;

                    course_node * next_node = current_competitor->course->course_nodes[next_node_index];

                    if (strcmp(next_node->type, "JN") == 0) {

                        current_competitor->last_logged_node = next_node;
                        current_competitor->current_status = 2;
                        current_competitor->last_logged_node_index = next_node_index;
                        current_competitor->current_progress = current_competitor->current_progress + 1;
                    }

                }

            }

        }

    }

    if (current->next != NULL) {

        updateOtherEntrants(current->next, new, time);

    }
}

void updateCurrentEntrantTrack(competitor * current_competitor) {

    int node1, node2;

    node1 = current_competitor->course->course_nodes[current_competitor->last_logged_node_index]->number;

    node2 = current_competitor->course->course_nodes[(current_competitor->last_logged_node_index) + 1]->number;

    linked_item * temp_item = track_list->head;

    while (temp_item != NULL) {

        course_track * temp_track = (course_track *) temp_item->item_data;

        if ((temp_track->start_node->number == node1 && temp_track->end_node->number == node2) || (temp_track->start_node->number == node2 && temp_track->end_node->number == node1)) {

            current_competitor->last_logged_track = temp_track;
        }

        temp_item = temp_item->next;

    }

}

int checkEntrantCompletedTrack(competitor * current_competitor, competitor * new_competitor) {

    int new_entrant_time = (new_competitor->last_cp_time.hour * 60) + (new_competitor->last_cp_time.minutes);

    int current_entrant_time = (current_competitor->last_cp_time.hour * 60) + (current_competitor->last_cp_time.minutes);

    int time_difference = new_entrant_time - current_entrant_time;

    if (time_difference > current_competitor->last_logged_track->minutes) {

        return 1;

    } else {

        return 0;
    }

}

void userUpdateEntrant(linked_item * entrant, int requested_no) {

    competitor * current_competitor = (competitor *) entrant->item_data;

    if (current_competitor->competitor_number == requested_no) {

        int node;
        char time[5];
        char course_id;
        int checkpoint_exists = 0;

        printf("\nEnter checkpoint number:\n");
        scanf(" %d", &node);

        int i;
        for (i = 0; i < current_competitor->course->course_length; i++) {

            if (current_competitor->course->course_nodes[i]->number == node && strcmp(current_competitor->course->course_nodes[i]->type, "CP") == 0) {

                checkpoint_exists = 1;

            }
        }

        if (checkpoint_exists == 1) {

            printf("\nEnter recorded for checkpoint time (HH:MM):\n");
            scanf(" %s", time);

            course_id = current_competitor->course_id;

            updateEntrant(entrant_list->head, course_id, node, requested_no, time);

        } else {
            printf("\nEntered node is not a checkpoint. Please try again.\n");
        }

    } else {

        if (entrant->next != NULL) {

            userUpdateEntrant(entrant->next, requested_no);

        } else {
            printf("\nEntrant cannot be located. Please try again.");
        }
    }
}
