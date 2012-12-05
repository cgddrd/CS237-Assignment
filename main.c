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
    
        if(loadEventDes() == 0) {
            
            printf("LOAD ERROR OCCURED!!");
            
        } else {
          
            printEventDes();
            
        };
        
        loadNodes();
        printNodes();
                
        loadTracks();
        printTracks();
        
        loadCourses();
        printCourses();
        
        loadCompetitors();
       /* printCompetitors(); */
                  
}

void displayMenu() {
   
    int option = 0;

    while (option != 8) {

        printf("\nWelcome, please select an option:\n");
        printf("\n*****************************************");
        printf("\n  1. Display competitors yet to start");
        printf("\n  2. Load time log file into system");
        printf("\n*****************************************\n");
        scanf(" %d", &option);

        switch(option) {

        case 1:
            printf("\nTotal competitors not started: ");
            break;
        case 2:
            loadTimes();
            getAllEntrantStatuses(); 
            break;
        case 3:
        {
            int entrant;
            printf("Enter required competitor number:\n");
            scanf(" %d", &entrant);
            userUpdateEntrant(entrant_list->head, entrant);
            getAllEntrantStatuses();
            break;
        }
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


