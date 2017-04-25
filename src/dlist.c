/*******************************************************************************************/

/*
* File: dlist.c
* Author: Coby Allred
* NetID: cobyallred
* Date: 10/5/16
*
* Description: Defines all functions used in creating / searching the doubly linked list
*
*/

/*******************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dlist.h"

/* creates a new list and initializes the head/tail */
void DListConstruct(DList* list) {
	if(list == NULL) return;

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return;
}

/* removes all items from the list, deallocating each item */
void DListDestruct(DList* list) {
	if(list == NULL) return;

	int i = 0;
	int size = list->size;

	for (i = 0; i < size; i++) { // Removes the head and auto increments
		DListRemove(list, list->head);
	}
	
	return;
}

/* inserts newNode after the given currNode */
void DListInsertAfter(DList* list, DListNode* currNode, DListNode* newNode) {
	if(list == NULL) return;

	DListNode* nextNode = NULL;

	if (currNode == NULL) { // List empty
		list->head = newNode;
		list->tail = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
		list->size = 1;
	}
	else if (currNode == list->tail) { // Insert after tail
		list->tail->next = newNode;
		newNode->prev = list->tail;
		newNode->next = NULL;
		list->tail = newNode;
		list->size = list->size + 1;
	}
	else { // Insert in middle
		nextNode = currNode->next;
		newNode->next = nextNode;
		newNode->prev = currNode;
		currNode->next = newNode;
		nextNode->prev = newNode;
		list->size = list->size + 1;
	}
	return;
}

/* inserts newNode before the given currNode */
void DListInsertBefore(DList* list, DListNode* currNode, DListNode* newNode) {
	if(list == NULL) return;

	DListNode* prevNode = NULL;

	if (currNode == NULL) { // List empty
		list->head = newNode;
		list->tail = newNode;
		list->size = 1;
	}
	else if (currNode == list->head) { // Insert before head
		list->head = newNode;
		newNode->prev = NULL;
		newNode->next = currNode;
		currNode->prev = newNode;
		list->size = list->size + 1;
	}
	else { // Insert in middle
		prevNode = currNode->prev;
		newNode->prev = prevNode;
		newNode->next = currNode;
		currNode->prev = newNode;
		prevNode->next = newNode;
		list->size = list->size + 1;
	}
	return;
}

/* return the first list node to match blankLength */
DListNode* DListSearch(DList* list, int blankLength) {
	if(list == NULL) return;

	DListNode* currNode = NULL; //Create traversal node
	currNode = list->head;

	while (currNode != NULL) { // 
		if (strlen(currNode->str)-1 == (unsigned)blankLength) { // If matching length, return
			return currNode;
		}
		currNode = currNode->next; // Increment
	}

	return NULL;
}

/* remove the list node (if it is a member of the list) */
void DListRemove(DList* list, DListNode* currNode) {
	if(list == NULL) return;
	if (currNode == NULL) return;

	DListNode* nextNode = currNode->next; // Find the next and prev nodes
	DListNode* prevNode = currNode->prev;
	
	list->size = list->size - 1;
	if (nextNode != NULL) { // Set next node prev pointer
		nextNode->prev = prevNode;
	}

	if (prevNode != NULL) { // Reset previous node pointer
		prevNode->next = nextNode;
	}

	if (currNode == list->head) { // Removed head
		list->head = nextNode;
	}

	if (currNode == list->tail) { // Removed tail
		list->tail = prevNode;
	}

	free(currNode); // Free memory

	return;
}

void DListRemoveNotFree(DList* list, DListNode* currNode) {
	if(list == NULL) return;
	if(currNode == NULL) return;

	DListNode* nextNode = currNode->next; // Find the next and prev nodes
	DListNode* prevNode = currNode->prev;

	list->size = list->size - 1;
	if (nextNode != NULL) { // Set next pointer
		nextNode->prev = prevNode;
	}

	if (prevNode != NULL) { // Set prev pointer
		prevNode->next = nextNode;
	}

	if (currNode == list->head) { // Removed head
		list->head = nextNode;
	}

	if (currNode == list->tail) { // Removed tail
		list->tail = prevNode;
	}

	return;
}