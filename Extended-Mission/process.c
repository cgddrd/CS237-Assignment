#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

void updateEntrant(linked_item * current, char type, int node, int entrant, char * time) {

    competitor * temp_competitor = (competitor *) current->data;

    int temp_bool = 0;

    if (temp_competitor->competitor_number == entrant) {

        if (checkExclusion(temp_competitor, type, node) == 0) {

            if (processMedicalCP(temp_competitor, type, node, time) == 0) {

                int i;

                for (i = 0; i < temp_competitor->course->course_length; i++) {

                    if (temp_competitor->course->course_nodes[i]->number == node && temp_bool != 1) {

                        if (i > (temp_competitor->current_progress - 1)) {

                            course_node * temp = temp_competitor->course->course_nodes[i];

                            if (strcmp(temp_competitor->course->course_nodes[i]->type, "CP") == 0) {

                                temp_competitor->current_status = 1;

                            } else if (strcmp(temp_competitor->course->course_nodes[i]->type, "JN") == 0) {

                                temp_competitor->current_status = 2;

                            }

                            temp_competitor->last_logged_node = temp;
                            temp_competitor->current_progress = i + 1;
                            temp_competitor->last_logged_node_index = i;
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


                        }
                    }
                }

            }

        }

        updateOtherEntrants(entrant_list->head, current, time);

    } else {

        if (current->next != NULL) {

            updateEntrant(current->next, type, node, entrant, time);

        } else {

            printf("\n\nEntrant cannot be located. Please try again.");
        }
    }

}

int checkExclusion(competitor * new_competitor, char type, int node) {

    if (new_competitor->current_status == 6 || new_competitor->current_status == 7) {

        return 1;

    } else {

        linked_item * temp = node_list->head;

        while (temp != NULL) {

            course_node * temp_node = (course_node *) temp->data;

            if (type == 'I') {

                new_competitor->current_status = 7;
                new_competitor->last_logged_node = temp_node;
                strcpy(new_competitor->finish_time, "DNF");
                return 1;

            } else if (type == 'E') {

                new_competitor->current_status = 6;
                new_competitor->last_logged_node = temp_node;
                strcpy(new_competitor->finish_time, "DNF");
                return 1;

            }

            temp = temp->next;

        }

    }

    return 0;

}

int processMedicalCP(competitor * new_competitor, char type, int node, char * time) {

    if (type == 'A') {

        strcpy(new_competitor->medical_cp_log.last_arrival_time, time);
        new_competitor->current_status = 5;

        linked_item * temp = node_list->head;

        while (temp != NULL) {

            course_node * temp_node = (course_node *) temp->data;

            if (temp_node->number == node) {

                new_competitor->last_logged_node = temp_node;

            }

            temp = temp->next;
        }

        int i;

        for (i = 0; i < new_competitor->course->course_length; i++) {

            if (new_competitor->course->course_nodes[i]->number == node && i > (new_competitor->current_progress) - 1) {

                new_competitor->last_logged_node_index = i;
                new_competitor->current_progress = i + 1;
                break;

            }

        }
        return 1;

    } else if (type == 'D') {

        strcpy(new_competitor->medical_cp_log.last_depart_time, time);
        new_competitor->medical_cp_log.total_delay =
                new_competitor->medical_cp_log.total_delay + calcMCDelay(new_competitor->medical_cp_log.last_arrival_time, new_competitor->medical_cp_log.last_depart_time);


        updateCurrentEntrantTrack(new_competitor);
        new_competitor->current_status = 3;

        return 0;

    }

    return 0;

}

int calcMCDelay(char * arrive_time, char * depart_time) {

    int arrive_hours, arrive_mins, depart_hours, depart_mins;

    char * arrive_hours_s = (char*) malloc(2);
    char * arrive_mins_s = (char*) malloc(2);
    char * depart_hours_s = (char*) malloc(2);
    char * depart_mins_s = (char*) malloc(2);

    strncpy(arrive_hours_s, arrive_time, 2);
    strncpy(arrive_mins_s, arrive_time + 3, 5);
    strncpy(depart_hours_s, depart_time, 2);
    strncpy(depart_mins_s, depart_time + 3, 5);

    arrive_hours = atoi(arrive_hours_s);
    arrive_mins = atoi(arrive_mins_s);
    depart_hours = atoi(depart_hours_s);
    depart_mins = atoi(depart_mins_s);

    int total_arrive_time = (arrive_hours * 60) + (arrive_mins);
    int total_depart_time = (depart_hours * 60) + (depart_mins);
    int delay = total_depart_time - total_arrive_time;

    free(arrive_hours_s);
    free(arrive_mins_s);
    free(depart_hours_s);
    free(depart_mins_s);

    return delay;

}

void convertTime(competitor * new_competitor, char * time_string) {

    char *hours = (char*) malloc(2);
    char *mins = (char*) malloc(2);

    strncpy(hours, time_string, 2);

    strncpy(mins, time_string + 3, 5);

    new_competitor->last_cp_time.hour = atoi(hours);

    new_competitor->last_cp_time.minutes = atoi(mins);

}

void updateOtherEntrants(linked_item * current_item, linked_item * new_item, char * time) {

    competitor * current_competitor = (competitor *) current_item->data;
    competitor * new_competitor = (competitor *) new_item->data;

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

    if (current_item->next != NULL) {

        updateOtherEntrants(current_item->next, new_item, time);

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

void userUpdateEntrant(linked_item * entrant, int requested_no) {

    competitor * current_competitor = (competitor *) entrant->data;

    if (current_competitor->competitor_number == requested_no) {

        int node, MC_choice, exc_choice, isMC, checkpoint_exists, exc_reason;
        char time[5];
        char course_id;

        printf("\nEnter checkpoint number:\n");
        scanf(" %d", &node);

        int i;
        for (i = 0; i < current_competitor->course->course_length; i++) {

            if (current_competitor->course->course_nodes[i]->number == node && strcmp(current_competitor->course->course_nodes[i]->type, "CP") == 0) {

                checkpoint_exists = 1;

            } else if (current_competitor->course->course_nodes[i]->number == node && strcmp(current_competitor->course->course_nodes[i]->type, "MC") == 0) {

                checkpoint_exists = 1;
                isMC = 1;
            }
        }

        if (checkpoint_exists == 1) {

            printf("\nEntrant excluded (1 = Yes, 2 = No):\n");
            scanf(" %d", &exc_choice);

            if (exc_choice == 1) {

                printf("\nEntrant reason (1 = Wrong CP, 2 = Failed Medical):\n");
                scanf(" %d", &exc_reason);

                if (exc_reason == 1) {

                    course_id = 'I';

                } else {

                    if (isMC != 1) {

                        printf("\nEntered CP not a medical CP. Entrant cannot have failed medical check.");
                        course_id = 'I';

                    } else {

                        course_id = 'E';

                    }
                }

            } else {

                if (isMC == 1) {

                    printf("\nArriving (1), Departing (2):\n");
                    scanf(" %d", &MC_choice);

                    if (MC_choice == 1) {

                        course_id = 'A';

                    } else {

                        course_id = 'D';

                    }

                } else {
                    course_id = current_competitor->course_id;

                }

            }

            printf("\nEnter recorded for checkpoint time (HH:MM):\n");
            scanf(" %s", time);

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
