/*******************************************************************************************/

/*
 * File: dlist.h
 * Author: Coby Allred
 * NetID: cobyallred
 * Date: 10/5/16
 *
 * Description: This contains the function prototypes used in processing all of the game's cards.
 *
 */

/*******************************************************************************************/

#ifndef CARDPROCESSING_H
#define CARDPROCESSING_H

/*******************************************************************************************/

// readInputCardsfile will take in an input file and add each valid card to the doubly linked list cardsList
int readInputCardsFile(DList* cardsList, char *filename);

// createCardNode will create a DListNode*, allocate its memory, and pass in the string, blankindex, and blanklength given
DListNode* createCardNode(char* string, int blankIndex, int blankLength);

// processCards will create processed cards out of unprocessed cards by first matching a string with equal length and replacing the card's blanks, sorting the list by total string length, and freeing the unprocessed cards and used strings
int processCards(DList cardsList[], DList stringsList[], DList processedCardsList[]);

// writeProcessedCards will write the final cards to a given output using the list processCardsList
int writeProcessedCards(DList processedCardsList[], char* fileName);

/*******************************************************************************************/

#endif // CARDPROCESSING_H

