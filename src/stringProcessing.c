/*******************************************************************************************/

/*
* File: stringProcessing.h
* Author: Coby Allred
* NetID: cobyallred
* Date: 10/5/16
*
* Description: Defines all of the string processing files to read from input files and create the DListNodes
*
*/

/*******************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dlist.h"
#include "stringProcessing.h"

#define MAX_STRING_LEN 1023

/*******************************************************************************************/
int readInputStringsFile(DList* stringsList, char *fileName) {
	char scanText[MAX_STRING_LEN];

	FILE* stringIn = NULL; // Open the file for reading
	stringIn = fopen(fileName, "r");

	if (stringIn == NULL) { // If file is null, return -1
		return -1;
	}
	else if (stringsList == NULL) { // If list is NULL, return -2
		return -2;
	}
	else {
		while (fgets(scanText, MAX_STRING_LEN, stringIn)) { // While not end of file
			int count = 0;
			int valid = 1;

			for (count = 0; (unsigned)count < strlen(scanText); count++) { // Increment through the string
				if (/*!isalnum(scanText[count]) && !ispunct(scanText[count]) ||*/ strlen(scanText) < 4) { // Checking for invalid string. Some commented out due to invalid characters in text files crashing program.
					count = strlen(scanText) + 1;
					valid = 0;
				}
			}

			if (valid == 1) { // If string is valid
				unsigned int endIndex; // Removing the return characters and replacing with null characters
				for (endIndex = 0; endIndex < strlen(scanText); endIndex++) {
					if (scanText[endIndex] == '\n' || scanText[endIndex] == '\r') {
						scanText[endIndex] = '\0';
					}
				}

				DListInsertAfter(stringsList, stringsList->tail, createStringNode(scanText)); // Add the new string to the end of the list
			}
		

		}
	}

	fclose(stringIn); // Close the input file
	return 0;

}

DListNode* createStringNode(char* string) {
	DListNode* node = (DListNode*)malloc(sizeof(DListNode)); // Allocating memory

	node->next = NULL; // Set next / prev pointers
	node->prev = NULL;
	node->blankIndex = -1; // Set -1 values
	node->blankLength = -1;
	node->str = (char*)malloc((strlen(string)+1) * sizeof(char)); // Allocate string memory
	strcpy(node->str, string); // Copy the new string in

	return node;
}