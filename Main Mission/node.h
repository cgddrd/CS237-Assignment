/* 
 * File: node.h
 * Description: Defines structure of course node functions used.
 * Author: Connor Luke Goddard (clg11)
 * Date: November 2012
 */

#ifndef NODE_H
#define	NODE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "linked_list.h"

    typedef struct node {
        int number;
        char type[2];

    } course_node;

    linked_item * linked_node;
    list * node_list;

    int loadNodes();
    void printNodes();


#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

