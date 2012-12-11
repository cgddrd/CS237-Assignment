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

    typedef struct time {
        int hour;
        int minutes;

    } logged_time;
    
    typedef struct med_cp {
        
        char last_arrival_time[6];
        char last_depart_time[6];
        int total_delay;
        
    } medical_cp; 

    typedef enum status {
        NOTSTARTED,
        CHECKPOINT,
        JUNCTION,
        TRACK,
        FINISHED,
                MEDICAL_CP,
                EXCLUDED_MEDICAL,
                EXCLUDED_IR
    } entrant_status;

    typedef struct entrant {
        int competitor_number;
        char course_id;
        char name[50];
        event_course * course;
        track_node * last_logged_node;
        course_track * last_logged_track;
        logged_time last_cp_time;
        medical_cp medical_cp_log;
        char last_logged_time[6];
        char start_time[6];
        char finish_time[6];
        int current_progress;
        entrant_status current_status;
        int last_logged_node_index;
    } competitor;

    linked_item * linked_entrant;
    list * entrant_list;

    int loadEntrants();
    int loadTimes();
    int checkEntrantCompletedTrack(competitor * current_competitor, competitor * new_competitor);
    void updateEntrant(linked_item * current, char type, int node, int entrant, char * time);
    void updateOtherEntrants(linked_item * current, linked_item * new, char * time);
    void getEntrantStatus(linked_item * entrant);
    void getAllEntrantStatuses();
    void userUpdateEntrant(linked_item * entrant, int requested_no);
    void convertTime(competitor * new_competitor, char * time_string);
    void updateCurrentEntrantTrack(competitor * current_competitor);
    void checkStarted();
    void checkNotStarted();
    void checkFinished();
    void displayResultsList();
    void getSpecificEntrantStatus();
    int checkExclusion(competitor * new_competitor, char type, int node);
    int processMedicalCP(competitor * new_competitor, char type, int node, char * time);
    int calcMCDelay(char * arrive_time, char * depart_time);


#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */
