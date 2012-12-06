#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "entrant.h"

int loadEntrants() {

    FILE * entrant_file = openFile("Enter entrants file name:");

    initialise(&entrant_list);

    if (entrant_file != NULL) {

        while (!feof(entrant_file)) {

            int status;

            linked_entrant = malloc(sizeof (linked_item));

            linked_entrant->next = NULL;

            competitor * new_competitor = malloc(sizeof (competitor));

            status = fscanf(entrant_file, " %d", &new_competitor->competitor_number);
            fscanf(entrant_file, " %c", &new_competitor->course_id);

            linked_item * temp_course = course_list->head;

            while (temp_course != NULL) {

                event_course * temp_event = (event_course *) temp_course->data;

                if (strcmp(&new_competitor->course_id, &temp_event->id) == 0) {

                    new_competitor->course = temp_event;

                }

                temp_course = temp_course->next;
            }

            fscanf(entrant_file, " %[a-zA-Z ]s", new_competitor->name);

            new_competitor->last_logged_node = NULL;
            new_competitor->current_progress = 0;
            new_competitor->current_status = 0;
            strcpy(new_competitor->start_time, "N/A"); 
            strcpy(new_competitor->finish_time, "N/A"); 
            linked_entrant->data = new_competitor;

            if (status > 0) {

                addToList(&linked_entrant, &entrant_list);

            }
        }

        fclose(entrant_file);
        return 1;

    } else {
        return 0;
    }
}

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

    competitor * temp_competitor = (competitor *) current->data;

    int temp_bool = 0;

    if (temp_competitor->competitor_number == entrant) {

        int j;

        for (j = 0; j < temp_competitor->course->course_length; j++) {

            if (temp_competitor->course->course_nodes[j]->number == node && temp_bool != 1) {

                if (j > (temp_competitor->current_progress - 1)) {

                    track_node * temp = temp_competitor->course->course_nodes[j];

                    if (strcmp(temp_competitor->course->course_nodes[j]->type, "CP") == 0) {

                        temp_competitor->current_status = 1;

                    } else if (strcmp(temp_competitor->course->course_nodes[j]->type, "JN") == 0) {

                        temp_competitor->current_status = 2;

                    }

                    temp_competitor->last_logged_node = temp;
                    temp_competitor->current_progress = j + 1;
                    temp_competitor->last_logged_node_index = j;

                   /* printf("NEW LAT LOGGED TIME: %s", temp_competitor->last_logged_time); */

                    if (temp_competitor->current_progress == 1) {

                        strcpy(temp_competitor->start_time, time); 
                        printf("NEW START TIME: %s", temp_competitor->start_time);
                    }
                    
                    printf("\nSTART TIME: %d, %s", temp_competitor->competitor_number, temp_competitor->start_time);

                    convertTime(temp_competitor, time);

                    temp_bool = 1;

                    if (temp_competitor->current_progress == temp_competitor->course->course_length) {

                        temp_competitor->current_status = 4;

                        strcpy(temp_competitor->finish_time, time);
                        
                        printf("\nFinish TIME: %d, %s", temp_competitor->competitor_number, temp_competitor->finish_time);
                    }

                    updateOtherEntrants(entrant_list->head, current, time);
                }
            }
        }

    } else {

        if (current->next != NULL) {

            updateEntrant(current->next, type, node, entrant, time);

        } else {

            printf("\nEntrant cannot be located. Please try again.");
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

    competitor * current_competitor = (competitor *) current->data;
    competitor * new_competitor = (competitor *) new->data;

    if (current_competitor->competitor_number != new_competitor->competitor_number) {

        if (strcmp(current_competitor->last_logged_time, time) != 0) {

            if (current_competitor->current_status == 1 || current_competitor->current_status == 2) {

                updateCurrentEntrantTrack(current_competitor);

                current_competitor->current_status = 3;

            } else if (current_competitor->current_status == 3) {

                if (checkEntrantCompletedTrack(current_competitor, new_competitor)) {

                    int next_node_index = (current_competitor->last_logged_node_index) + 1;

                    track_node * next_node = current_competitor->course->course_nodes[next_node_index];

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

        course_track * temp_track = (course_track *) temp_item->data;

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

void getEntrantStatus(linked_item * entrant) {

    competitor * temp_competitor = (competitor *) entrant->data;

    char status[20];
    
    printf("\nWANKER TWAT: %d, %s", temp_competitor->competitor_number, temp_competitor->start_time);

    switch (temp_competitor->current_status) {

        case 0:
            strcpy(status, "Not Started");
            break;
        case 1:
            strcpy(status, "Checkpoint");
            break;
        case 2:
            strcpy(status, "Junction");
            break;
        case 3:
            strcpy(status, "Track");
            break;
        case 4:
            strcpy(status, "Finished");
            break;
        default:
            strcpy(status, "Unknown");
            break;

    }

    printf("\nCompetitor %d (%s) -> Current Status: %s, Current Progress: %d, Start Time: %s, End Time: %s", temp_competitor->competitor_number,
            temp_competitor->name, status, temp_competitor->current_progress, temp_competitor->start_time, temp_competitor->finish_time);

}

void getAllEntrantStatuses() {

    linked_item * temp = entrant_list->head;

    while (temp != NULL) {

        getEntrantStatus(temp);
        temp = temp->next;

    }
}

void userUpdateEntrant(linked_item * entrant, int requested_no) {

    competitor * current_competitor = (competitor *) entrant->data;

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

void checkNotStarted() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |                      Competitor Name                   |   Current Status  |");
    printf("\n|==================|========================================================|===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        if (current_competitor->current_status == 0) {

            char status[12];

            switch (current_competitor->current_status) {

                case 0:
                    strcpy(status, "Not Started");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", current_competitor->competitor_number, current_competitor->name, status);
            printf("\n|------------------|--------------------------------------------------------|-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nAll competitors are currently on a course\n");
    } else {
        printf("\nTotal competitors yet to start: %d\n", count);
    }

}

void checkStarted() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |                      Competitor Name                   |   Current Status  |");
    printf("\n|==================|========================================================|===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        if (current_competitor->current_status > 0 || current_competitor->current_status < 4) {

            char status[12];

            switch (current_competitor->current_status) {

                case 1:
                    strcpy(status, "Checkpoint");
                    break;
                case 2:
                    strcpy(status, "Junction");
                    break;
                case 3:
                    strcpy(status, "Track");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", current_competitor->competitor_number, current_competitor->name, status);
            printf("\n|------------------|--------------------------------------------------------|-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo competitors are currently on the course\n");
    } else {
        printf("\nTotal competitors out on course: %d\n", count);
    }

}

void checkFinished() {

    linked_item * temp = entrant_list->head;

    int count = 0;

    printf("\n|  Competitor No   |                      Competitor Name                   |   Current Status  |");
    printf("\n|==================|========================================================|===================|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        if (current_competitor->current_status == 4) {

            char status[12];

            switch (current_competitor->current_status) {

                case 4:
                    strcpy(status, "Finished");
                    break;
                default:
                    strcpy(status, "Unknown");
                    break;
            }

            printf("\n| %8d         |   %-50s   |    %-12s   |", current_competitor->competitor_number, current_competitor->name, status);
            printf("\n|------------------|--------------------------------------------------------|-------------------|");

            count++;

        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo competitors have currently finished.\n");

    } else {
        printf("\nTotal competitors finished: %d\n", count);
    }
}

void displayResultsList() {

    linked_item * temp = entrant_list->head;

    printf("\n|  Competitor No   |                      Competitor Name                   |   Current Status  |   Start Time  |   End Time  |");
    printf("\n|==================|========================================================|===================|===============|=============|");

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->data;

        char status[12];

        switch (current_competitor->current_status) {

            case 0:
                strcpy(status, "Not Started");
                break;
            case 1:
                strcpy(status, "Checkpoint");
                break;
            case 2:
                strcpy(status, "Junction");
                break;
            case 3:
                strcpy(status, "Track");
                break;
            case 4:
                strcpy(status, "Finished");
                break;
            default:
                strcpy(status, "Unknown");
                break;
        }

        printf("\n| %8d         |   %-50s   |    %-12s   |      %-5s    |    %-5s    |",

                current_competitor->competitor_number,
                current_competitor->name,
                status,
                current_competitor->start_time,
                current_competitor->finish_time);

        printf("\n|------------------|--------------------------------------------------------|-------------------|---------------|-------------|");
        temp = temp->next;
    }

}
