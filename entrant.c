#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "entrant.h"

void loadCompetitors() {

    FILE * entrant_file = openFile("Enter entrants file name:");

    entrant_list = malloc(sizeof (list));
    
    entrant_list->head = NULL;
    entrant_list->tail = NULL;

    if (entrant_file != NULL) {

        /*int count = 0;

        // no_of_competitors = countLines(entrant_file);

        // rewind(entrant_file); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)

        //dynamic allocation of array - same as: "track_node nodeArray[lines];"
        //competitor_collection = calloc(1, no_of_competitors * sizeof (competitor)); */

        while (!feof(entrant_file)) {

            int status;

            linked_entrant = malloc(sizeof (linked_item));
            
            linked_entrant->next = NULL;

            competitor * new_competitor = malloc(sizeof (competitor));

            /*/new_entrant->data = new_competitor; */


            status = fscanf(entrant_file, " %d", &new_competitor->competitor_number);
            fscanf(entrant_file, " %c", &new_competitor->course_id);

            /* fscanf(entrant_file, " %d", &competitor_collection[count].competitor_number); //& needed here when using scan because you need a pointer to the 
            // first element - not needed with string as it is an array of chars.

            //  fscanf(entrant_file, " %s", competitor_collection[count].course_id); */

            int i;
            
            linked_item * temp_course = course_list->head;
            
            while (temp_course !=NULL) {
                
                   event_course * temp_event = (event_course *) temp_course->data;
       
                   if (strcmp(&new_competitor->course_id, &temp_event->id) == 0) {

                    /* competitor_collection[count].course = &course_collection[i]; */

                    new_competitor->course = temp_event;

                }
                
                   temp_course = temp_course->next;
                
            }



            /* fscanf(entrant_file, " %[a-zA-Z ]s", competitor_collection[count].name); */

            fscanf(entrant_file, " %[a-zA-Z ]s", new_competitor->name);

            new_competitor->last_logged_node = NULL;
            new_competitor->current_progress = 0;

            entrant_status new_status = NOTSTARTED;

            new_competitor->current_status = new_status;

            linked_entrant->data = new_competitor;

            /*  competitor_collection[count].current_checkpoint = NULL;
            // competitor_collection[count].current_progress = 0; */

            if (status > 0) {

                if (entrant_list->head == NULL) {

                    entrant_list->head = linked_entrant;
                    entrant_list->tail = linked_entrant;

                } else {

                    linked_item * temp = entrant_list->tail;

                    /*       while (temp->next !=NULL) {
                                
                               temp = temp->next;
                                
                           } */

                    temp->next = linked_entrant;
                    entrant_list->tail = linked_entrant;
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
            
            updateEntrant(entrant_list->head, type, node, entrant_no, time);

        }

        fclose(time_file);



    } else {

        printf("\nFAIL!! - Cannot load file.");
    }
}

void updateEntrant(linked_item * current, char type, int node, int entrant, char * time) {
    
    competitor * temp_competitor = (competitor *) current->data;

    int temp_bool = 0;

    if (temp_competitor->competitor_number == entrant) {

        int j;

        for (j = 0; j < temp_competitor->course->course_length; j++) {

            if (temp_competitor->course->course_nodes[j]->number == node && temp_bool != 1) {
                

                if (j > (temp_competitor->current_progress - 1)) {

                    track_node * temp = temp_competitor->course->course_nodes[j];

                    if (strcmp(temp_competitor->course->course_nodes[j]->type, "CP") == 0) {

                        entrant_status new_status = CHECKPOINT;

                        temp_competitor->current_status = new_status;

                    } else if (strcmp(temp_competitor->course->course_nodes[j]->type, "JN") == 0) {


                        entrant_status new_status = JUNCTION;

                        temp_competitor->current_status = new_status;
                    }

                    temp_competitor->last_logged_node = temp;

                    temp_competitor->current_progress = j + 1;
                    
                    strcpy(temp_competitor->last_logged_time, time);
                    
                     if (temp_competitor->current_progress == 1) {
                        
                        strcpy(temp_competitor->start_time, time);
                     }
                    
                    temp_competitor->last_logged_node_index = j;
                    
            
                char *hours = (char*) malloc(2);
                char *mins = (char*) malloc(2);
                strncpy(mins, time+3, 5);
                strncpy(hours, time, 2);
                
                temp_competitor->test_time.hour = atoi(hours);
                
                temp_competitor->test_time.minutes = atoi(mins);

                    temp_bool = 1;

                    if (temp_competitor->current_progress == temp_competitor->course->course_length) {

                        entrant_status new_status = FINISHED;

                        temp_competitor->current_status = new_status;
                        
                        strcpy(temp_competitor->finish_time, time);
                        
                        

                    }
                    
                    updateOtherEntrants(entrant_list->head, current, time);


                }



            }


        }

    } else {

        if (current->next != NULL) {

        updateEntrant(current->next, type, node, entrant, time);

         } else {
            
            printf("\nEntrant cannot be located. Please try again.");
        }
    
        
    }

}

void updateOtherEntrants(linked_item * current, linked_item * new, char * time) {
    
    competitor * current_competitor = (competitor *) current->data;
    
    competitor * new_competitor = (competitor *) new->data;
    
    if (current_competitor->competitor_number != new_competitor->competitor_number) {

                if (strcmp(current_competitor->last_logged_time, time) != 0) {

                    if (current_competitor->current_status == 1 || current_competitor->current_status == 2) {

                        int node1, node2;

                        node1 = current_competitor->course->course_nodes[current_competitor->last_logged_node_index]->number;

                        node2 = current_competitor->course->course_nodes[(current_competitor->last_logged_node_index) + 1]->number;

                        int i;
                        
                        linked_item * temp_item = track_list->head;
                        
                        while (temp_item != NULL) {
                            
                            course_track * temp_track = (course_track *) temp_item->data;
                            
                            if ((temp_track->start_node->number == node1 && temp_track->end_node->number == node2) || (temp_track->start_node->number == node2 && temp_track->end_node->number == node1))
                                {
                                
                                current_competitor->last_logged_track = temp_track;
                            }
                            
                            temp_item = temp_item->next;
                            
                        } 
                        
                        current_competitor->current_status = 3;
                        
                    } else if (current_competitor->current_status == 3) {
                        
                        int new_entrant_time = (new_competitor->test_time.hour * 60) + (new_competitor->test_time.minutes);
                        
                        int current_entrant_time = (current_competitor->test_time.hour * 60) + (current_competitor->test_time.minutes);
                        
                        int time_difference = new_entrant_time - current_entrant_time;
                        
                        
                    /*    if (time_difference > current_track.minutes) {
                            
                            printf("\nCurrent competitor %d should move onto their next checkpoint", current->data->competitor_number);
                            
                        } else {
                           
                            printf("\nCurrent competitor %d has not reached the end of their track -> track %d", current->data->competitor_number, current_track.number);
                            
                        } */
                        
                        if (time_difference > current_competitor->last_logged_track->minutes) {
                       
                       int next_node = (current_competitor->last_logged_node_index) + 1;
                       
                       track_node * twat = current_competitor->course->course_nodes[next_node];
                       
                       if (strcmp(twat->type, "JN") == 0) {
                           
                           current_competitor->last_logged_node = twat;
                           current_competitor->current_status = 2;
                           current_competitor->last_logged_node_index = next_node;
                           current_competitor->current_progress = current_competitor->current_progress + 1;
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

        updateOtherEntrants(current->next, new, time);

         } 
}

void getEntrantStatus(linked_item * entrant) {
    
    competitor * temp_competitor = (competitor *) entrant->data;
    
    char status[20];
    
    switch(temp_competitor->current_status) {

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
    
    printf("\nCompetitor %d (%s) -> Current Status: %s, Current Progress: %d", temp_competitor->competitor_number,
            temp_competitor->name, status, temp_competitor->current_progress);
     
}

void getAllEntrantStatuses() {
    
    linked_item * temp = entrant_list->head;
    
    while (temp !=NULL) {
        
        getEntrantStatus(temp);
        temp = temp->next;
        
    }
    
    
}

void userUpdateEntrant(linked_item * entrant, int requested_no) {
    
    competitor * current_competitor = (competitor *) entrant->data;

    if (current_competitor->competitor_number == requested_no) {
       
       int node;
       char time[5];
       char course_id;
       
       int accept_bool = 0;
       
       printf("\nEnter checkpoint number:\n");
       scanf(" %d", &node);
       
       int i;
       
       for (i = 0; i < current_competitor->course->course_length; i++) {
           
           if (current_competitor->course->course_nodes[i]->number == node && strcmp(current_competitor->course->course_nodes[i]->type,"CP") == 0) {
               
              accept_bool = 1; 
               
               
           }

       }
           
           if (accept_bool == 1) {
       
                               printf("\nEnter recorded for checkpoint time (HH:MM):\n");
       scanf(" %s", time);
       
       course_id = current_competitor->course_id;
       
       updateEntrant(entrant_list->head, course_id, node, requested_no, time);  
               
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



