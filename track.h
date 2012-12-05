/* 
 * File:   track.h
 * Author: connor
 *
 * Created on November 24, 2012, 4:53 PM
 */

#ifndef TRACK_H
#define	TRACK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "node.h"
#include "linked_list.h"
    
    struct track {
     
        int number;
        track_node * start_node;
        track_node * end_node;
        int minutes;
     
    };
    
    typedef struct track course_track;

   linked_item * linked_track;
   list * track_list;
    
    void loadTracks();
    void printTracks();



#ifdef	__cplusplus
}
#endif

#endif	/* TRACK_H */

