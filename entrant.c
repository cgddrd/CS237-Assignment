#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "entrant.h"

void loadCompetitors() {

    FILE * entrant_file = openFile("Enter entrants file name:");

    list = malloc(sizeof (entrant_list));

    if (entrant_file != NULL) {

        /*int count = 0;

        // no_of_competitors = countLines(entrant_file);

        // rewind(entrant_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)

        //dynamic allocation of array - same as: "track_node nodeArray[lines];"
        //competitor_collection = calloc(1, no_of_competitors * sizeof (competitor)); */

        while (!feof(entrant_file)) {

            int status;

            linked_entrant * new_entrant = malloc(sizeof (linked_entrant));

            competitor * new_competitor = malloc(sizeof (competitor));

            /*/new_entrant->data = new_competitor; */


            status = fscanf(entrant_file, " %d", &new_competitor->competitor_number);
            fscanf(entrant_file, " %c", &new_competitor->course_id);

            /* fscanf(entrant_file, " %d", &competitor_collection[count].competitor_number); //& needed here when using scan because you need a pointer to the 
            // first element - not needed with string as it is an array of chars.

            //  fscanf(entrant_file, " %s", competitor_collection[count].course_id); */

            int i;

            for (i = 0; i < no_of_courses; i++) {


                /*     if (strcmp (competitor_collection[count].course_id, course_collection[i].id) == 0) {
                                                        
                             competitor_collection[count].course = &course_collection[i];
                            
                      } */

                if (strcmp(&new_competitor->course_id, course_collection[i].id) == 0) {

                    /* competitor_collection[count].course = &course_collection[i]; */

                    new_competitor->course = &course_collection[i];

                }

            }

            /* fscanf(entrant_file, " %[a-zA-Z ]s", competitor_collection[count].name); */

            fscanf(entrant_file, " %[a-zA-Z ]s", new_competitor->name);

            new_competitor->last_logged_node = NULL;
            new_competitor->current_progress = 0;

            entrant_status new_status = NOTSTARTED;

            new_competitor->current_status = new_status;

            new_entrant->data = new_competitor;

            /*  competitor_collection[count].current_checkpoint = NULL;
            // competitor_collection[count].current_progress = 0; */

            if (status > 0) {

                if (list->head == NULL) {

                    list->head = new_entrant;
                    list->tail = new_entrant;

                } else {

                    linked_entrant * temp = list->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = new_entrant;
                    list->tail = new_entrant;
                }


            }
            /* printf("STATUS: %d", status); */
        }

        fclose(entrant_file);

    } else {

        printf("\nFAIL!! - Cannot load file.");
    }
}


void loadTimes() {

    FILE * time_file = openFile("Enter time file name:");

    if (time_file != NULL) {

        int node;
        int entrant_no;
        char time[5];
        char type;


        while (!feof(time_file)) {

            fscanf(time_file, " %c", &type); 
            fscanf(time_file, " %d", &node);

            fscanf(time_file, " %d", &entrant_no);

            fscanf(time_file, " %[0-9:]s", time);
            
            update2(list->head, type, node, entrant_no, time);

        }

        fclose(time_file);



    } else {

        printf("\nFAIL!! - Cannot load file.");
    }
}

void update2(linked_entrant * current, char type, int node, int entrant, char * time) {

    int temp_bool = 0;

    if (current->data->competitor_number == entrant) {

        int j;

        for (j = 0; j < current->data->course->course_length; j++) {

            if (current->data->course->course_nodes[j]->number == node && temp_bool != 1) {
                

                if (j > (current->data->current_progress - 1)) {

                    track_node * temp = current->data->course->course_nodes[j];

                    if (strcmp(current->data->course->course_nodes[j]->type, "CP") == 0) {

                        entrant_status new_status = CHECKPOINT;

                        current->data->current_status = new_status;

                    } else if (strcmp(current->data->course->course_nodes[j]->type, "JN") == 0) {


                        entrant_status new_status = JUNCTION;

                        current->data->current_status = new_status;
                    }

                    current->data->last_logged_node = temp;

                    current->data->current_progress = j + 1;
                    
                    strcpy(current->data->last_logged_time, time);
                    
                     if (current->data->current_progress == 1) {
                        
                        strcpy(current->data->start_time, time);
                     }
                    
                    current->data->last_logged_node_index = j;
                    
            
                char *hours = (char*) malloc(2);
                char *mins = (char*) malloc(2);
                strncpy(mins, time+3, 5);
                strncpy(hours, time, 2);
                
                current->data->test_time.hour = atoi(hours);
                
                current->data->test_time.minutes = atoi(mins);

                    temp_bool = 1;

                    if (current->data->current_progress == current->data->course->course_length) {

                        entrant_status new_status = FINISHED;

                        current->data->current_status = new_status;
                        
                        strcpy(current->data->finish_time, time);
                        
                        

                    }
                    
                    updateOthers(list->head, current, time);


                }



            }


        }

    } else {

        if (current->next != NULL) {

        update2(current->next, type, node, entrant, time);

         } else {
            
            printf("\nEntrant cannot be located. Please try again.");
        }
    
        
    }

}

void updateOthers(linked_entrant * current, linked_entrant * new, char * time) {
    
    if (current->data->competitor_number != new->data->competitor_number) {

                if (strcmp(current->data->last_logged_time, time) != 0) {

                    if (current->data->current_status == 1 || current->data->current_status == 2) {

                        int node1, node2;

                        node1 = current->data->course->course_nodes[current->data->last_logged_node_index]->number;

                        node2 = current->data->course->course_nodes[(current->data->last_logged_node_index) + 1]->number;

                        int i;

                        for (i = 0; i < no_of_tracks; i++) {
                           

                            if ((track_collection[i].start_node->number == node1 && track_collection[i].end_node->number == node2) || (track_collection[i].start_node->number == node2 && track_collection[i].end_node->number == node1))
                                {
                                
                                current->data->last_logged_track_index = i;
                            }
                        }
                        
                        current->data->current_status = 3;
                        
                    } else if (current->data->current_status == 3) {
                        
                        course_track current_track = track_collection[current->data->last_logged_track_index];
                        
                        int new_entrant_time = (new->data->test_time.hour * 60) + (new->data->test_time.minutes);
                        
                        int current_entrant_time = (current->data->test_time.hour * 60) + (current->data->test_time.minutes);
                        
                        int time_difference = new_entrant_time - current_entrant_time;
                        
                        
                    /*    if (time_difference > current_track.minutes) {
                            
                            printf("\nCurrent competitor %d should move onto their next checkpoint", current->data->competitor_number);
                            
                        } else {
                           
                            printf("\nCurrent competitor %d has not reached the end of their track -> track %d", current->data->competitor_number, current_track.number);
                            
                        } */
                        
                        if (time_difference > current_track.minutes) {
                       
                       int next_node = (current->data->last_logged_node_index) + 1;
                       
                       track_node * twat = current->data->course->course_nodes[next_node];
                       
                       if (strcmp(twat->type, "JN") == 0) {
                           
                           current->data->last_logged_node = twat;
                           current->data->current_status = 2;
                           current->data->last_logged_node_index = next_node;
                           current->data->current_progress = current->data->current_progress + 1;
                       }
                       
                       /* for (j = 0; j < current->data->course->course_length; j++) {
                           
                           if (j > (current->data->current_progress - 1)) {
                               
                             track_node * temp = current->data->course->course_nodes[j];
                             
                             if (strcmp(temp->type, "JN") == 0) {
                                 
                                //current->data->current_checkpoint = temp;
                                 
                                current->data->current_status = 2;

                                current->data->current_progress = j + 1; 
                                 
                             }
                               
                               
                           }
                           
                           
                           
                       } */
                        
                        
                    }
                        
                    }

                }


            


        }
    
     if (current->next != NULL) {

        updateOthers(current->next, new, time);

         } 
}

void getEntrantStatus(linked_entrant * entrant) {
    
    char status[20];
    
    switch(entrant->data->current_status) {

        case 0:
            strcpy(status, "Not Started");
            break;
        case 1:
            strcpy(status, "Checkpoint");
            break;
        case 2:
            strcpy(status, "Junction");
            break;
        case 3:
            strcpy(status, "Track");
            break;
        case 4:
            strcpy(status, "Finished");
            break;
        default:
           strcpy(status, "Unknown");
           break;
                
        }
    
    printf("\nCompetitor %d (%s) -> Current Status: %s, Current Progress: %d", entrant->data->competitor_number,
            entrant->data->name, status, entrant->data->current_progress);
     
}

void getAllEntrantStatuses() {
    
    linked_entrant * temp = list->head;
    
    while (temp->next !=NULL) {
        
        getEntrantStatus(temp);
        temp = temp->next;
        
    }
    
    
}

void userUpdateEntrant(linked_entrant * entrant, int requested_no) {

    if (entrant->data->competitor_number == requested_no) {
       
       int node;
       char time[5];
       char course_id;
       
       int accept_bool = 0;
       
       printf("\nEnter checkpoint number:\n");
       scanf(" %d", &node);
       
       int i;
       
       for (i = 0; i < entrant->data->course->course_length; i++) {
           
           if (entrant->data->course->course_nodes[i]->number == node && strcmp(entrant->data->course->course_nodes[i]->type,"CP") == 0) {
               
              accept_bool = 1; 
               
               
           }

       }
           
           if (accept_bool == 1) {
       
                               printf("\nEnter recorded for checkpoint time (HH:MM):\n");
       scanf(" %s", time);
       
       course_id = entrant->data->course_id;
       
       update2(list->head, course_id, node, requested_no, time);  
               
           } else {
               
              printf("\nEntered node is not a checkpoint. Please try again.\n"); 
               
           }
        
        
        
    } else {
        
        if (entrant->next !=NULL) {
            
            userUpdateEntrant(entrant->next, requested_no);
            
        } else {
            
            printf("\nEntrant cannot be located. Please try again.");
        }
    }
    
    
    
    
    
}



