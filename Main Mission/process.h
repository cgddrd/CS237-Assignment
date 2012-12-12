/* 
 * File: process.h
 * Description: Defines functions that are utilised by process.c and called
 * from other source files.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "linked_list.h"
#include "entrant.h"
#include "fileIO.h"

    void userUpdateEntrant(linked_item * entrant, int requested_no);
    void convertTime(competitor * new_competitor, char * time_string);
    void updateCurrentEntrantTrack(competitor * current_competitor);
    int checkEntrantCompletedTrack(competitor * current_competitor, competitor * new_competitor);
    void updateEntrant(linked_item * current, char type, int node, int entrant, char * time);
    void updateOtherEntrants(linked_item * current, linked_item * new, char * time);
    int loadTimes();

#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_H */

