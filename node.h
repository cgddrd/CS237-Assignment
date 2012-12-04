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
    struct track * tracks_list;
     
};

typedef struct node track_node;

typedef track_node * track_node_ptr;

    typedef struct node_list_item linked_node;
    
    struct node_list_item {
    
    track_node * data;
    linked_node * next;
    
    };
   
    struct node_linked_list {
    
    linked_node * head;
    linked_node * tail;
    int no_of_items;
    
   };
   
   typedef struct node_linked_list node_list;
   
    node_list * nodelist;

track_node * node_collection;

int no_of_nodes;

void loadNodes();
void printNodes();


#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

