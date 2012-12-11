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
    void getEntrantStatus(linked_item * entrant);
    void getAllEntrantStatuses();
    void getSpecificEntrantStatus();

#ifdef	__cplusplus
}
#endif

#endif	/* ENTRANT_H */

