/* 
 * File:   entrant.h
 * Author: connor
 *
 * Created on November 24, 2012, 7:58 PM
 */

#ifndef ENTRANT_H
#define	ENTRANT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "course.h"
        #include "track.h"
#include "linked_list.h"

    struct time {
        
        int hour;
        int minutes;
        
    };
    
    typedef struct time logged_time;
    
    typedef enum status {
        NOTSTARTED,
        CHECKPOINT,
        JUNCTION,
        TRACK,
        FINISHED
    } entrant_status;

    typedef struct entrant {
     
        int competitor_number;
        char course_id;
        char name[50];
        event_course * course;
        track_node * last_logged_node;
        course_track * last_logged_track;
        logged_time test_time; 
        char last_logged_time[5];
        char start_time[5];
        char finish_time[5];
        int current_progress;
        entrant_status current_status;
        int last_logged_node_index;
        int last_logged_track_index;
               
    } competitor;
    
        linked_item * linked_entrant;
        list * entrant_list;

    void loadCompetitors();
    void loadTimes();
    void updateEntrant (linked_item * current, char type, int node, int entrant, char * time);
    void updateOtherEntrants(linked_item * current, linked_item * new, char * time);
    void getEntrantStatus(linked_item * entrant);
    void getAllEntrantStatuses();
    void userUpdateEntrant(linked_item * entrant, int requested_no);

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

