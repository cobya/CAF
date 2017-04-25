/*******************************************************************************************/

/*
* File: cardProcessing.c
* Author: Coby Allred
* NetID: cobyallred
* Date: 10/5/16
*
* Description: cardProcessing contains all of the functions necessary to process both input and the final processing of the cards. 
* It will contain the functions readInputCardsFile, createCardNode, processCards, and writeProcessCards
*
*/

/*******************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dlist.h"
#include "cardProcessing.h"

#define MAX_STRING_LEN 1023

/*******************************************************************************************/

int readInputCardsFile(DList* cardsList, char *fileName) {
	char holdText[MAX_STRING_LEN];

	FILE* cardInput = NULL; // Open the specified file to be read
	cardInput = fopen(fileName, "r");

	if (cardInput == NULL) { // If unable to open the file, return -1
		return -1;
	}
	else if (cardsList == NULL) { // If list is NULL, return -2
		return -2;
	} 
	else {
		while (fgets(holdText, MAX_STRING_LEN, cardInput)) { // Continue reading the file until the end is reached
			int count = 0; // For loop counting variable
			int blankLen = 0; // Length of blank
			int blankCounter = 0; // Number of seperate blanks
			int blankLoc = -1; // Blank index location

			for (count = 0; (unsigned)count < strlen(holdText); count++) { // Search the string for invalid data and location of the blank
				if (/*!isalnum(holdText[count]) && !ispunct(holdText[count]) || */ strlen(holdText) < 4) { // If any char is not valid or string not long enough, stop for loop and skip creating this card
																																					// Some commented out due to invalid characters in text files crashing program.
					count = strlen(holdText) + 1;
					blankCounter = -1;
				}
				else {
					if (holdText[count] == '_') { // Checking for underscore blanks
						blankLen = 1; // Set blankLen to 1
						if (blankLoc == -1) { // Set the first new blank location
							blankLoc = count; 
						}

						int count2 = count; // New counter so the initial loop is not changed
						for (count2 = count; (unsigned)count2 < strlen(holdText); count2++) { // Checking to see the length of the blank
							if (holdText[count2 + 1] == '_') { // Increments through string to find more blank spaces
								blankLen += 1;
							}
							else { // If the blank ends, end the for loop
								count2 = strlen(holdText) + 1;
							}
						}
						
						if (blankLen >= 3) {
							blankCounter += 1; // Found a blank, so increase count of total blanks
							break;
						}
						else {
							blankLen = 0; // If blank is not valid, reset
							blankLoc = -1;
						}
					}
						
				}
			}

			if (blankCounter == 1) { // If there is only one valid blank and the card is valid, begin card creation
				unsigned int endIndex; // Replace any newline characters with null characters
				for (endIndex = 0; endIndex < strlen(holdText); endIndex++) {
					if (holdText[endIndex] == '\n' || holdText[endIndex] == '\r') {
						holdText[endIndex] = '\0';
					}
				}
				
				DListNode* newCard = createCardNode(holdText, blankLoc, blankLen); // Creates the new string's node and adds it to the end of the list
				DListInsertAfter(cardsList, cardsList->tail, newCard);
				
			}

		}
	}

	fclose(cardInput); // Close the file

	return 0; // Return 0 if successful

}

DListNode* createCardNode(char* string, int blankIndex, int blankLength) {
	DListNode* node = (DListNode*)malloc(sizeof(DListNode)); // Allocating memory

	node->next = NULL; // Setting links to NULL
	node->prev = NULL;
	node->blankIndex = blankIndex; // Setting node data to data passed in from function
	node->blankLength = blankLength;
	node->str = (char*)malloc((strlen(string)+1) * sizeof(char)); // Allocating exact string memory
	strcpy(node->str, string); // Copying in the new string

	return node;
}

int processCards(DList cardsList[], DList stringsList[], DList processedCardsList[]) {
	if (cardsList == NULL || stringsList == NULL || processedCardsList == NULL) { // If any lists are NULL, return -1
		return -1;
	}

	DListNode *unProcNode = cardsList->head; // Making processed card node

	while (unProcNode != NULL && stringsList != NULL) { // Going through all of the unprocessed cards
		DListNode* stringNode = NULL;

		for (stringNode = stringsList->head; stringNode != NULL; stringNode = stringNode->next) { // Increment through all strings
			if (strlen(stringNode->str) == (unsigned)unProcNode->blankLength) { // If lengths are the same

				strncpy(unProcNode->str + unProcNode->blankIndex, stringNode->str, strlen(stringNode->str)); // Copy string into card node

				DListNode* insertNode = createCardNode(unProcNode->str, unProcNode->blankIndex, unProcNode->blankLength); // Creates the node to be inserted
				DListNode* currNode = processedCardsList->head; // Creates a node used to search the processedCardsList
				int added = 0;
				while (added == 0) {
					if (processedCardsList->head == NULL) { // If the list is empty, create a head node
						DListInsertBefore(processedCardsList, NULL, insertNode);
						added = 1;
					}
					else if (strlen(insertNode->str) < strlen(currNode->str)) { // If strlen < current strlen, insert before
						DListInsertBefore(processedCardsList, currNode, insertNode);
						added = 1;
					}
					else if (strlen(insertNode->str) == strlen(currNode->str)) { // If strlen = current strlen, insert after
						DListInsertAfter(processedCardsList, currNode, insertNode);
						added = 1;
					}
					else if (strlen(insertNode->str) > strlen(currNode->str) && currNode->next == NULL) { // If end of list and still greater, insert after
						DListInsertAfter(processedCardsList, processedCardsList->tail, insertNode);
						added = 1;
					}
					else if (strlen(insertNode->str) > strlen(currNode->str) && currNode->next != NULL) { // If not end of list and greater, increment list
						currNode = currNode->next;
					}
					else {
						printf("Error inserting processed card.\n");
						break;
					}
				}
				break;
			}
		}
		DListRemove(stringsList, stringNode); // Removes the used string from its list and free
		unProcNode = unProcNode->next; // Increments node
		DListRemove(cardsList, cardsList->head); // Removes used card
	}

	return 0;
}

int writeProcessedCards(DList processedCardsList[], char* fileName) {
	if (processedCardsList == NULL) { // If list is NULL, return -1
		return -2;
	}
	
	FILE* cardOutput = NULL; // Open the specified file to written to
	cardOutput = fopen(fileName, "w");

	if (cardOutput == NULL) { // If unable to open the file, return -1
		return -1;
	}

	DListNode *currNode = processedCardsList->head; // Creates node to increment

	while (currNode != NULL) { // Increments through list and prints output
		fprintf(cardOutput, "%s\n", currNode->str);
		currNode = currNode->next;
	}

	fclose(cardOutput); // Close the file

	return 0;
}