/**************************************************************************************************/

/*
 * File: main.c
 * Author: Coby Allred
 * NetID: cobyallred
 * Date: 10/5/16
 *
 * Description: Spork program finds nearby and good restaurants/businesses.
 *
 */

/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"
#include "cardProcessing.h"
#include "stringProcessing.h"

int main(int argc, char *argv[]) {

	if( argc != 4 ) { // If the user enters the incorrect # of params, print usage and exit
		printf("Usage: chars inputCardsFile inputStringsFile outputFile\n");
		return -1;
	}

	DList cardsList; // Creating the unprocessed cards linked list
	DListConstruct(&cardsList);
	DList stringList;;// Creating the unprocessed strings linked list
	DListConstruct(&stringList);
	DList processedCards; // Creating the processed cards linked list
	DListConstruct(&processedCards);

	int valid = 0; // Creating a valid check variable for function returns

	valid = readInputCardsFile(&cardsList, argv[1]); // Read input cards
	if (valid == -1) {
		printf("Failure reading from %s. Exiting.\n", argv[1]);
		return -1;
	}
	else if (valid == -2) {
		printf("Error: List is NULL.");
	}

	valid = readInputStringsFile(&stringList, argv[2]); // Read input Strings
	if (valid == -1) {
		printf("Failure reading from %s. Exiting.\n", argv[1]);
		return -1;
	}
	else if (valid == -2) {
		printf("Error: List is NULL.");
	}

	valid = processCards(&cardsList, &stringList, &processedCards); // Process the cards
	if (valid == -1) {
		printf("Error: One or more lists is NULL.\n");
	}

	valid = writeProcessedCards(&processedCards, argv[3]); // Write the output file
	if (valid == -2) {
		printf("Error: Processed list is NULL.\n");
	}
	else if (valid == -1) {
		printf("Failure writing to %s. Exiting.\n", argv[3]);
	}

	// Destroying each list and freeing the memory
	DListDestruct(&cardsList);
	free(&cardsList);
	DListDestruct(&stringList);
	free(&stringList);
	DListDestruct(&processedCards);
	free(&processedCards);

	return;


}