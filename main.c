/* 
 * File:   main.c
 * Author: connor
 *
 * Created on November 16, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "node.h"
#include "fileIO.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
        loadEventDes();

        loadNodes();
        printNodes();
        
        int i = 0;
        
           for (i=0; i < no_of_nodes; i++) {
               
             printf("\nWANKER %d: %d -> %s", i, n[i].number, n[i].type);  
               
           }

    return (EXIT_SUCCESS);
}



