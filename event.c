#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "fileIO.h"

int loadEventDes() {

    event = calloc(1, sizeof (event_description));

    FILE * event_file = openFile("Enter event description file name:");

    if (event_file != NULL) {
        
        while (!feof(event_file)) {

            fscanf(event_file, " %[A-Za-z -]s", event -> event_title);
            fscanf(event_file, " %[a-zA-Z0-9 ]s", event -> event_date);
            fscanf(event_file, " %[0-9:]s", event -> event_time);

        }

        fclose(event_file);

    } else {
        
        free(event_file);
        return 0;
    }

    return 1;
}

void printEventDes() {

    printf("\n%s\n%s\n%s\n ", event->event_title, event->event_date, event->event_time);

}