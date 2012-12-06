/* 
 * File:   main.c
 * Author: connor
 *
 * Created on November 16, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main(int argc, char** argv) {

    loadFiles();
    displayMenu();

    return (EXIT_SUCCESS);
}

void checkFileLoad(int (*functionPtr)(), void (*printfunctionPtr)()) {

    while (functionPtr() == 0) {

        printf("\nFile could not be opened.\nWould you like to try again? (1 = Yes, 2 = No):\n");
        int option;

        scanf(" %d", &option);

        switch (option) {

            case 1:
                functionPtr(); 
                break;
            case 2:
                printf("\nExiting program.");
                exit(0);
                break;
            default:
                printf("\nOption not available - Exiting program.");
                exit(0);
                break;
        }

    }
    
    printfunctionPtr();
}

void loadFiles() {

    checkFileLoad(&loadEventDes, &printEventDes);
    
    checkFileLoad(&loadNodes, &printNodes);

    checkFileLoad(&loadTracks, &printTracks);
    
    checkFileLoad(&loadCourses, &printCourses);
    
    checkFileLoad(&loadEntrants, &getAllEntrantStatuses);

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

        switch (option) {

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


