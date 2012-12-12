/* 
 * File: entrant.c
 * Description: Creates new entrant structures and populates them with
 * data supplied from file read-in by system.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "entrant.h"

/* 
 * Creates new instance of entrant structure and populates with
 * data read-in from a file.
 */
int loadEntrants() {

    /* Obtain course FILE pointer returned by openFile (fileIO.c). */
    FILE * entrant_file = openFile("Enter entrants file name:");

    /* Allocate memory for course linked-list data structure (fileIO.c). */
    initialise(&entrant_list);

    if (entrant_file != NULL) {
        
        int status = 0;

        /* Read file until EOF is reached. */
        while (!feof(entrant_file)) {

            /* Create new linked-list item. */
            linked_entrant = malloc(sizeof (linked_item));
            linked_entrant->next = NULL;

            /* Create new entrant structure and allocated required memory. */
            competitor * new_competitor = malloc(sizeof (competitor));

            status = fscanf(entrant_file, " %d", 
                    &new_competitor->competitor_number);
            
            fscanf(entrant_file, " %c", &new_competitor->course_id);

            linked_item * temp_item = course_list->head;

            /* Search through all courses for matching entrant course ID. */            
            while (temp_item != NULL) {

                event_course * temp_course = (event_course *) temp_item->item_data;

                /* If current course ID matches the specified
                 * course ID new entrant is registered for, 
                 * set pointer in entrant to course. */
                if (new_competitor->course_id == temp_course->id) {

                    new_competitor->course = temp_course;

                }

                temp_item = temp_item->next;
            }

            fscanf(entrant_file, " %[a-zA-Z ]s", new_competitor->name);

            /* Set default values to entrant location,
             * status and current progress variables. */
            new_competitor->last_logged_node = NULL;
            new_competitor->current_progress = 0;
            new_competitor->current_status = 0;
            strcpy(new_competitor->start_time, "N/A");
            strcpy(new_competitor->finish_time, "N/A");
            
            /* Set new linked list item data to new entrant structure. */
            linked_entrant->item_data = new_competitor;

            /* Check course information was read in successfully from file 
             * (data not incomplete/corrupt)
             */
            if (status > 0) {

                /* Add new item to course linked list. */
                addToList(&linked_entrant, &entrant_list);

            }
        }

        /* Once all lines have been read in, close the file. */
        fclose(entrant_file);
        return 1;

    } else {
        
         /* If an error has occurred, return flag indicating this. */
        return 0;
    }
}

/* 
 * Obtains the current status of an entrant (passed as parameter)
 * and prints this to standard output.
 */
void getEntrantStatus(linked_item * entrant) {

    competitor * temp_competitor = (competitor *) entrant->item_data;

    char status[20];

    /* Determine status and print out required value to screen. */
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

    printf("\nCompetitor %d (%s) -> Current Status: %s, Current Progress: %d, "
            "Start Time: %s, End Time: %s\n\n", 
            temp_competitor->competitor_number,
            temp_competitor->name,
            status, 
            temp_competitor->current_progress, 
            temp_competitor->start_time, 
            temp_competitor->finish_time);

}

/* 
 * Loop through all entrants in linked list and print out
 * current status and information for each.
 */
void getAllEntrantStatuses() {

    linked_item * temp = entrant_list->head;

    while (temp != NULL) {

        getEntrantStatus(temp);
        temp = temp->next;

    }
}

/* 
 * Display current status of an entrant specified by the
 * user via input prompt.
 */
void getSpecificEntrantStatus() {

    int entrant, entrantFound = 0;
    printf("Enter required competitor number:\n");
    scanf(" %d", &entrant);

    linked_item * temp = entrant_list->head;

    while (temp != NULL) {

        competitor * current_competitor = (competitor *) temp->item_data;

        /* Check if competitor number entered by user exists. */
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