/* 
 * File: entrant.h
 * Description: Defines the structure of an entrant,
 * (with relevant time/checkpoint structures) and defines functions used.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef ENTRANT_H
#define	ENTRANT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "course.h"
#include "track.h"
#include "linked_list.h"

    /* Defines last logged time used 
     * for predicting entrant location */
    typedef struct time {
        int hour;
        int minutes;
    } logged_time;

    /* Defines enumerations used to 
     * specify entrant current status/location */
    typedef enum status {
        NOTSTARTED,
        CHECKPOINT,
        JUNCTION,
        TRACK,
        FINISHED
    } entrant_status;

    typedef struct entrant {
        int competitor_number;
        char course_id; /* Denotes ID of course entrant is registered for */
        char name[50];
        event_course * course; /* Used to access nodes of course */
        course_node * last_logged_node; /* Used to access last node data */
        int last_logged_node_index; /* Index of last logged node from course */
        course_track * last_logged_track; /* Used to access last track data */
        logged_time last_cp_time; /* Used for entrant time comparison */
        char last_logged_time[6]; /* String representation of last logged time */
        char start_time[6];
        char finish_time[6];
        int current_progress; /* Defines the current progress along course */
        entrant_status current_status; /* Defines current status as enum */
    } competitor;

    /* Define linked-list structure for entrants */
    linked_item * linked_entrant;
    list * entrant_list;

    int loadEntrants();
    void getEntrantStatus(linked_item * entrant);
    void getAllEntrantStatuses();
    void getSpecificEntrantStatus();


#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

