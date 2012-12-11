/* 
 * File:   display.h
 * Author: connor
 *
 * Created on December 11, 2012, 3:04 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include "entrant.h"

    void checkStarted();
    void checkNotStarted();
    void checkFinished();
    void displayResultsList();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

