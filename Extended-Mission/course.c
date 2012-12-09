#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "course.h"

int loadCourses() {

    FILE * course_file = openFile("Enter courses file name:");

    initialise(&course_list);

    if (course_file != NULL) {

        int status = 0;

        while (!feof(course_file)) {

            linked_course = malloc(sizeof (linked_item));

            linked_course->next = NULL;

            event_course * new_course = malloc(sizeof (event_course));

            status = fscanf(course_file, " %c%d", &new_course->id, &new_course->course_length);

            new_course->course_nodes = calloc(1, new_course->course_length * sizeof (track_node));
            
            compareCourseNodes(&new_course, &course_file);

            linked_course->data = new_course;

            if (status > 0) {

                addToList(&linked_course, &course_list);
            }
        }

        fclose(course_file);
        return 1;

    } else {
        return 0;
    }
}

void compareCourseNodes(event_course ** temp_course, FILE ** course_file) {

    int i;
    int current_node;


    for (i = 0; i < (*temp_course)->course_length; i++) {

        fscanf((*course_file), " %d", &current_node);


        linked_item * temp_item = node_list->head;

        while (temp_item != NULL) {

            track_node * temp_node = (track_node *) temp_item->data;

            if (current_node == temp_node->number) {

                (*temp_course)->course_nodes[i] = temp_node;

            }

            temp_item = temp_item->next;
        }
    }
}

void printCourses() {

    linked_item * temp = course_list->head;

    while (temp != NULL) {

        event_course * temp_event = (event_course *) temp->data;

        printf("\nCourse ID: %c, Length: %d", temp_event->id, temp_event->course_length);
        printf("\nNodes in course:");

        int i;
        for (i = 0; i < temp_event->course_length; i++) {

            printf("\nNode %d: No: %d, ID: %s", i, temp_event->course_nodes[i]->number, temp_event->course_nodes[i]->type);


        }

        printf("\n\n");

        temp = temp->next;

    }

}


