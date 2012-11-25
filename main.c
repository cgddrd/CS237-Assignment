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

void loadFiles();
void displayMenu();

/*
 * 
 */
int main(int argc, char** argv) {
    
    loadFiles();
    
    displayMenu();


    return (EXIT_SUCCESS);
}

void loadFiles() {
    
        loadEventDes();
        printEventDes();

        loadNodes();
        printNodes();
                
        loadTracks();
        printTracks();
        
        loadCourses();
        printCourses();
        
        loadCompetitors();
        printCompetitors();
      
}

void displayMenu() {
   
    int option;

    while (option != 8) {

        printf("\nWelcome, please select an option:\n");
        scanf(" %d", &option);

        switch(option) {

        case 1:
            printf("\nTotal competitors not started: %d", checkNotStarted());
            break;
        case 2:
            printf("\nDiick2\n");
            break;
        case 3:
            printf("\nDiick3\n");
            break;
        case 5:
            printf("\nDiick5\n");
            break;
        case 8:
            printf("\nThanks for using this program!\n");
            break;
        default:
           printf("\nnot allowed\n"); 
           break;
                
        }
        
    }
    
}


