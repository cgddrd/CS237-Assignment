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

    typedef struct track {
        int number;
        track_node * start_node;
        track_node * end_node;
        int minutes;

    } course_track;

    linked_item * linked_track;
    list * track_list;

    int loadTracks();
    void printTracks();
    void locateNodes(course_track * new_track, int start_node, int end_node);

#ifdef	__cplusplus
}
#endif

#endif	/* TRACK_H */

