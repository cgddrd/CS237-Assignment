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

    struct time {
        
        int hour;
        int minutes;
        
    };
    
    typedef struct time logged_time;

    struct entrant {
     
        int competitor_number;
        char course_id;
        char name[50];
        event_course * course;
        track_node * current_checkpoint;
       // logged_time time;
        char time[5];
        int current_progress;
               
    };
    
    typedef struct entrant competitor;
    
    typedef struct linked_list_item linked_entrant;

    struct linked_list_item {
    
    competitor * data;
    linked_entrant * next;
    
    };
    
    struct linked_list {
    
    linked_entrant * head;
    linked_entrant * tail;
    int no_of_items;
    
   };
   
   typedef struct linked_list entrant_list;
    
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

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

