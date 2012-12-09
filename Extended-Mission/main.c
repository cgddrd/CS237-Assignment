/* 
 * File:   main.c
 * Author: connor
 *
 * Created on November 16, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        printf("\n*****************************************");
        printf("\nWelcome, please select an option:\n");
        printf("\n*****************************************");
        printf("\n  1. Display competitors yet to start");
        printf("\n  2. Display competitors out of courses");
        printf("\n  3. Display finished competitors");
        printf("\n  4. Enter competitor checkpoint time");
        printf("\n  5. Load time log file into system");
        printf("\n  6. Display event results list");
        printf("\n  7. Display specific competitor status");
        printf("\n  8. Exit Program");
        printf("\n*****************************************\n");
        scanf(" %d", &option);

        switch (option) {

            case 1:
            {
                char test1[6];
                char test2[6];
                
                int wank;
                
                strcpy(test1, "09:27");
                strcpy(test2, "09:55");
                
                wank = calcMCDelay(test1, test2);
                
                printf("TEST MC DELAY VALUE: %d", wank);
                //checkNotStarted();
                break;
                
            }
            case 2:
                checkStarted();
                break;
            case 3:
                checkFinished();
                break;
            case 4:
            {
                int entrant;
                printf("Enter required competitor number:\n");
                scanf(" %d", &entrant);
                userUpdateEntrant(entrant_list->head, entrant);
                break;
            }
            case 5:
                loadTimes();
                break;
            case 6:
                displayResultsList();
                break;
            case 7:
                getSpecificEntrantStatus();
                break;
            case 8:
                printf("\nExiting program..\n");
                break;
            default:
                printf("\nInput not valid. Please try again.\n");
                break;

        }

    }

}


