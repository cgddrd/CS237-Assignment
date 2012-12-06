/* 
 * File:   main.h
 * Author: connor
 *
 * Created on December 6, 2012, 12:37 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "event.h"
#include "node.h"
#include "fileIO.h"
#include "track.h"
#include "course.h"
#include "entrant.h"

    void loadFiles();
    void displayMenu();
    int (*functionPtr)();
    void (*printfunctionPtr)();
    void checkFileLoad(int (*functionPtr)(), void (*printfunctionPtr)());



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

