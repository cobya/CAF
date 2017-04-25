/*******************************************************************************************/

/*
 * File: stringProcessing.c
 * Author: Coby Allred
 * NetID: cobyallred
 * Date: 10/5/16
 *
 * Description: Function prototypes for all of the string processing
 *
 */

/*******************************************************************************************/

#ifndef STRINGPROCESSING_H
#define STRINGPROCESSING_H

/*******************************************************************************************/

// Reads the input strings from a given file and puts them into a doubly linked list
int readInputStringsFile(DList* stringsList, char *filename);

// Creates a DListNode* given a certain string, setting other data to -1
DListNode* createStringNode(char* string);

/*******************************************************************************************/

#endif // STRINGPROCESSING_H

