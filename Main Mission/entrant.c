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

                event_course * temp_event = (event_course *) temp_course->item_data;

                if (new_competitor->course_id == temp_event->id) {

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
            linked_entrant->item_data = new_competitor;

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

void getEntrantStatus(linked_item * entrant) {

    competitor * temp_competitor = (competitor *) entrant->item_data;

    char status[20];

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

    printf("\nCompetitor %d (%s) -> Current Status: %s, Current Progress: %d, Start Time: %s, End Time: %s\n\n", temp_competitor->competitor_number,
            temp_competitor->name, status, temp_competitor->current_progress, temp_competitor->start_time, temp_competitor->finish_time);

}

void getAllEntrantStatuses() {

    linked_item * temp = entrant_list->head;

    while (temp != NULL) {

        getEntrantStatus(temp);
        temp = temp->next;

    }
}

void getSpecificEntrantStatus() {

    int entrant;
    int entrantFound = 0;
    printf("Enter required competitor number:\n");
    scanf(" %d", &entrant);

    linked_item * temp = entrant_list->head;

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->item_data;

        if (current_competitor->competitor_number == entrant) {

            getEntrantStatus(temp);
            entrantFound = 1;
        }

        temp = temp->next;
    }

    if (entrantFound == 0) {

        printf("\nCompetitor with number %d cannot be found. Please try again.", entrant);
    }
}

