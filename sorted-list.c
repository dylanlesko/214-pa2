#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#endif

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
	SortedListPtr sl = malloc(sizeof(SortedListPtr));
	//malloc memory for the compare function
	sl->CompareFuncT = malloc(sizeof(CompareFuncT));
	sl->CompareFuncT = cf;
	//malloc memory for the destruct function
	sl->DestructFuncT = malloc(sizeof(DestructFuncT));
	sl->DestructFuncT = df;
	//initialize the head node of the list to NULL
	sl->head = malloc(sizeof(SortedListPtr));
	
		
	return sl;
}


int SLInsert ( SortedListPtr list, void *newObj ) {
	//Create a new node, and mallocs memory for future elements
	SortedListPtr newNode = (SortedListPtr)malloc(sizeof(SortedListPtr));
	SortedListPtr previous = list->head;
	//SortedListPtr current = previous->next;

	//newNode
	//for now, put the new element into this newNode
	newNode->element = newObj;
	

	//If the list is new, this new element is now the head
	//if( list->head == NULL ) {return 1; }
	
	//If this is the first element in the list
	if( list->head->next == NULL ) {
		//int var to store return value of cmp function
		//int cmpVar = list->CompareFuncT( list->head->element, newObj );

		newNode->element = newObj;
		previous->next = newNode;

	}
	//If the list has been started
	else {

		
		SortedListPtr current = list->head->next;
		int cmpVar = list->CompareFuncT( current->element, newObj );
		previous = current;
		
		
		
		//If there is one element in the list
		if(previous->next == NULL)
		{
			if ( cmpVar < 0 ) {
				newNode->element = newObj;
				newNode->next = previous;
				list->head->next = newNode;
				return 1;
			}
			else if ( cmpVar > 0)
			{
				newNode->element = newObj;
				current->next = newNode;
				list->head->next = current;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		//If the new element is larger than the current pointer to the list
		if( cmpVar < 0 ) {
			newNode->next = previous;
			list->head->next = newNode;
			return 1;
		}
		if( cmpVar == 0)
			return 0;
		//If the new element is smaller than the current pointer, loop
		//until you find where it belongs
		cmpVar = list->CompareFuncT( current->element, newObj );
		while ( current != NULL && cmpVar > 0 ) {
			//If there are two elements in the list
			if( current->next == NULL ) {
				previous = current;
				cmpVar = -1;
			}
			else {
				previous = current;
				current = current->next;
				cmpVar = list->CompareFuncT( current->element, newObj );
			}
		}

		//Checks if the newele is larger than the last element in the list
		if( cmpVar < 0 ) {
			newNode->next = previous->next;
			previous->next = newNode;			
			return 1;
		}
		else if (cmpVar == 0) return 0;
		//If the new element is smaller than the last element, append
		//it to the end
		else { previous->next = newNode; return 1; }	
	}
}


int SLRemove(SortedListPtr list, void *newObj) {
	//If there is no elements, just exit
	if( list->head == NULL ) { return 0; }

	//create nodes to store current and next elements
    SortedListPtr previous = list->head->next;
    SortedListPtr current = previous->next;
    //store return value of CompareFuncT in int
    int varCmp = list->CompareFuncT( previous->element, newObj );
    
    //If the head is equal to the newObj, CUT OFF THEIR HEAD
    if( varCmp == 0 ) { list->head = NULL; return 0; }
			varCmp = list->CompareFuncT( current->element, newObj );

	//Loop until either the end of the list is reached, or there is a cmp match
    while ( previous != NULL && varCmp != 0 ) {
		previous = current;
		
		if(current->next != NULL)
		{
			current = current->next;
		
			varCmp = list->CompareFuncT( current->element, newObj );
		}
		else
		{
			break;
			current = current->next;
		}
    }
    //After the while loop ends, there should either be a match, or no more elements

    //If there is a match
    if( varCmp == 0 ) { 

			current = current->next;
			previous->next = current;
		
		
		return 1;
	}
	//If there is no match, it's the end of the list, return error int
    else { return 0; }
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	//Creates a pointer to the linkedlist
	SortedListIteratorPtr s = malloc(sizeof(SortedListIteratorPtr));
	s->head = list->head->next;	
	s->finished = false;
	
	//printf("\nwell: %d", *(int*)s->head->element);
	
	return s; 
}
	
	
void SLDestroy(SortedListPtr list){
	SortedListPtr current = list->head->next;
	SortedListPtr next = current->next;
	while(current != NULL) {
		free(current->element);
		free(current->head);
		if(current->next != NULL)
		{
			next = next->next;
			current = next;
		}
		else
		{
			free(current);
			break;
		}
	}
	free(list->head);
	free(list->element);
	free(list->next);
	} 
void SLDestroyIterator(SortedListIteratorPtr iter){
	free(iter);
	} 
void * SLGetItem( SortedListIteratorPtr iter ) { 
	if ( iter->head == NULL )
	{
		return 0;
	}
	else
	{

		//printf("\nreturn: %d", *(int*) iter->head->element);
		return iter->head->element;
	}
}

void * SLNextItem(SortedListIteratorPtr iter) { 
	if( iter->head == NULL)
	{
		return NULL;
	}

	if( iter->head->next == NULL ) {
		SortedListPtr previous = iter->head;
		iter->head = previous->next;
		iter->finished = true;

		return NULL;
	}
	else {
		SortedListPtr previous = iter->head;
		iter->head = previous->next;

		return previous->next->element; 
		//return NULL;
	}
}
