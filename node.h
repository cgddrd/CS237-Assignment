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

 struct node {
     
    int number;
    char type[2];
     
};

typedef struct node track_node;

typedef track_node * track_node_ptr;

track_node * node_collection;

int no_of_nodes;

void loadNodes();
void printNodes();


#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

