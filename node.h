/* 
 * File:   node.h
 * Author: connor
 *
 * Created on November 18, 2012, 9:49 AM
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

    } track_node;

    linked_item * linked_node;
    list * node_list;

    void loadNodes();
    void printNodes();


#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

