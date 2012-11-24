#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "fileIO.h"

void loadNodes() 
{
    
       FILE * file_two = openFile("Enter node file name:");
       
       
       
       if (file_two != NULL) {
           
         
          // int lines = 0;
           int count = 0;
           
           no_of_nodes = countLines(file_two);
           
           rewind(file_two); //Resets the file pointer back to the beginning - could also use fseek(fp, 0)
           
           //dynamic allocation of array - same as: "track_node nodeArray[lines];"
           node_collection = calloc(1, no_of_nodes * sizeof(track_node)); 
           
           while(!feof(file_two)) { 
               
                fscanf(file_two, " %d", &node_collection[count].number); //& needed here when using scan because you need a pointer to the 
                                                               // first element - not needed with string as it is an array of chars.

                fscanf(file_two, " %[A-Za-z]s", node_collection[count].type);
   
                count++;
               
           }
           
           fclose(file_two);
           
       } else {
           
          printf("\nFAIL!! - Cannot load file.");
       }
}

void printNodes() 
{
         int i = 0;
         for (i=0; i < no_of_nodes; i++) {
               
             printf("\nNode %d: %d -> %s", i, node_collection[i].number, node_collection[i].type);  
               
           }
    
}


