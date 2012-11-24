#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "fileIO.h"

void loadEventDes() {
    
    event_description *evt = calloc(1, sizeof(event_description));
    
    event_description * temp_event = evt;
    
    FILE * file = openFile("Enter event description file name:");
       
    fscanf(file, " %[A-Za-z -]s", temp_event -> event_title);
    fscanf(file, " %[a-zA-Z0-9 ]s", temp_event -> event_date);
    fscanf(file, " %[0-9:]s", temp_event -> event_time);
       
    fclose(file);
       
    printf("\n%s\n%s\n%s\n ", temp_event->event_title, temp_event->event_date, temp_event->event_time);
    
    
}

