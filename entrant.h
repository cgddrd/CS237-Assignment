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

    struct entrant {
     
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
               
    };
    
    typedef struct entrant competitor;
   

    typedef struct entrant_list_item linked_entrant;
    
    struct entrant_list_item {
    
    competitor * data;
    linked_entrant * next;
    
    };
   
    struct entrant_linked_list {
    
    linked_entrant * head;
    linked_entrant * tail;
    int no_of_items;
    
   };
   
   typedef struct entrant_linked_list entrant_list;
    
    competitor * competitor_collection;
    
    entrant_list * list;
    
    
    
    
    int no_of_competitors;
    
    void loadCompetitors();
    void displayList(linked_entrant * current);
    void printCompetitors();
    int checkNotStarted();
    int checkStarted();
    void loadTimes();
    void updateEntrant(char * type, int node, int entrant, char * time);
    void update (char * type, int node, int entrant, char * time);
    void update2 (linked_entrant * current, char type, int node, int entrant, char * time);
    void updateOthers(linked_entrant * current, linked_entrant * new, char * time);
    void getEntrantStatus(linked_entrant * entrant);
    void getAllEntrantStatuses();
    void userUpdateEntrant(linked_entrant * entrant, int requested_no);

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

