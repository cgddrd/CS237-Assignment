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
    FILE * openFile();


    int countLines(char *file_name);
    


#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */

