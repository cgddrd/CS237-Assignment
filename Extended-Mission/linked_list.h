/* 
 * File:   linked_list.h
 * Author: connor
 *
 * Created on December 4, 2012, 9:28 PM
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct list_item {
    
    void * data;
    struct list_item * next;
    
    } linked_item;
    
   
    typedef struct linked_list {
    
    linked_item * head;
    linked_item * tail;
    int no_of_items;
    
   } list;
   
   void initialise();


#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

