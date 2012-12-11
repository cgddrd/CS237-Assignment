/* 
 * File:   event.h
 * Author: connor
 *
 * Created on November 16, 2012, 10:05 AM
 */

#ifndef EVENT_H
#define	EVENT_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct event {
        char event_title[79];
        char event_date[79];
        char event_time[5];
    } event_description;

    event_description * event;

    int loadEventDes();
    void printEventDes();


#ifdef	__cplusplus
}
#endif

#endif	/* EVENT_H */
