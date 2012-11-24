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
#include "track.h"
#include "course.h"
#include "entrant.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
        loadEventDes();

        loadNodes();
        printNodes();
                
        loadTracks();
        printTracks();
        
        loadCourses();
        printCourses();
        
        loadCompetitors();
        printCompetitors();

    return (EXIT_SUCCESS);
}



