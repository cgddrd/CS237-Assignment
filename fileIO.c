#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"

void initialise(list ** data_list) {

    (*data_list) = malloc(sizeof (list));

    (*data_list)->head = NULL;
    (*data_list)->tail = NULL;

}

void addToList(linked_item ** new_item, list ** data_list) {

    if ((*data_list)->head == NULL) {

        (*data_list)->head = (*new_item);
        (*data_list)->tail = (*new_item);

    } else {

        linked_item * temp = (*data_list)->tail;

        temp->next = (*new_item);
        (*data_list)->tail = (*new_item);
    }
}

FILE * openFile(char * prompt) {

    char file_name[101];

    printf("\n%s ", prompt);
    scanf(" %100[a-zA-Z0-9._/]", file_name);

    FILE * file = fopen(file_name, "r");

    return file;

}