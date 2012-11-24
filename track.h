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
    
    struct track {
     
        int number;
        track_node * start_node;
        track_node * end_node;
        int minutes;
     
    };
    
    typedef struct track course_track;

    typedef course_track * course_track_ptr;
    
    int no_of_tracks;

    course_track * track_collection;
    
    void loadTracks();
    void printTracks();



#ifdef	__cplusplus
}
#endif

#endif	/* TRACK_H */

