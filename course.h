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
    
    struct course {
     
        char id[1];
        int course_length;
        track_node ** course_nodes;
        
    };
    
    typedef struct course event_course;

    typedef event_course * event_course_ptr;
    
    event_course * course_collection;
    
    int no_of_courses;
    
    void loadCourses();
    void printCourses();


#ifdef	__cplusplus
}
#endif

#endif	/* COURSE_H */

