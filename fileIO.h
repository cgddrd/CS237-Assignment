/* 
 * File:   fileIO.h
 * Author: connor
 *
 * Created on November 19, 2012, 11:44 AM
 */

#ifndef FILEIO_H
#define	FILEIO_H


#ifdef	__cplusplus
extern "C" {
#endif
    
#include "linked_list.h"
    
    FILE * openFile();
    void initialise(list ** data_list);
    int addToList(linked_item ** temp, list ** data_list);
    
#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */

