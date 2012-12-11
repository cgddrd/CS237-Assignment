/* 
 * File:   process.h
 * Author: connor
 *
 * Created on December 11, 2012, 6:51 PM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "linked_list.h"
#include "entrant.h"
#include "fileIO.h"


    int loadTimes();
    int checkExclusion(competitor * new_competitor, char type, int node);
    int processMedicalCP(competitor * new_competitor, char type, int node, char * time);
    int calcMCDelay(char * arrive_time, char * depart_time);
    void userUpdateEntrant(linked_item * entrant, int requested_no);
    void convertTime(competitor * new_competitor, char * time_string);
    void updateCurrentEntrantTrack(competitor * current_competitor);
    int checkEntrantCompletedTrack(competitor * current_competitor, competitor * new_competitor);
    void updateEntrant(linked_item * current, char type, int node, int entrant, char * time);
    void updateOtherEntrants(linked_item * current, linked_item * new, char * time);


#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_H */

