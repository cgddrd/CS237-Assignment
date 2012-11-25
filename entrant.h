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

    struct entrant {
     
        int competitor_number;
        char course_id[1];
        char name[50];
        event_course * course;
        track_node * current_checkpoint;
               
    };
    
    typedef struct entrant competitor;

    typedef competitor * competitor_ptr;
    
    competitor * competitor_collection;
    
    int no_of_competitors;
    
    void loadCompetitors();
    void printCompetitors();
    int checkNotStarted();
    int checkStarted();

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

