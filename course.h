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
     
        char id;
        int course_length;
        track_node ** course_nodes;
        
    };
    
    typedef struct course event_course;

    typedef event_course * event_course_ptr;
    
         typedef struct course_list_item linked_course;
    
    struct course_list_item {
    
    event_course * data;
    linked_course * next;
    
    };
   
    struct course_linked_list {
    
    linked_course * head;
    linked_course * tail;
    int no_of_items;
    
   };
   
   typedef struct course_linked_list course_list;
   
    course_list * courselist;
    
    event_course * course_collection;
    
    int no_of_courses;
    
    void loadCourses();
    void printCourses();


#ifdef	__cplusplus
}
#endif

#endif	/* COURSE_H */

