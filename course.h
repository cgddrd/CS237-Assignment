/* 
 * File:   course.h
 * Author: connor
 *
 * Created on November 24, 2012, 6:23 PM
 */

#ifndef COURSE_H
#define	COURSE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "node.h"
#include "linked_list.h"

    typedef struct course {
        
        char id;
        int course_length;
        track_node ** course_nodes;

    } event_course;


    linked_item * linked_course;
    list * course_list;

    int loadCourses();
    void compareCourseNodes(event_course ** temp_course, FILE ** course_file);
    void printCourses();


#ifdef	__cplusplus
}
#endif

#endif	/* COURSE_H */

