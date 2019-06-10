/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
   Create empty queue.
   Return NULL if could not allocate space.
   */
queue_t *q_new()
{
	queue_t *q =  malloc(sizeof(queue_t));
	/* What if malloc returned NULL? */
	if (q == NULL){
		return NULL;
	}	
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
	/* How about freeing the list elements and the strings? */
	/* Free queue structure */
	if (q != NULL){
		q->tracker = q->head;
		while (q->head != NULL){
			q->head = q->head->next;
			free(q->tracker->value);
			free(q->tracker);
			q->tracker = q->head;
		}
		free(q);
	}	
}

/*
   Attempt to insert element at head of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
   */
bool q_insert_head(queue_t *q, char *s)
{
	list_ele_t *newh; //new head
	char *str; //string being inserted

	if (q == NULL){
		return false;
	}

	newh = malloc(sizeof(list_ele_t));
	if (newh == NULL){
		return false;
	}
	/* Don't forget to allocate space for the string and copy it */
	str = malloc(strlen(s)+1);
	if (str == NULL){
		free(newh);
		return false;
	}
	strcpy(str, s); //puts the char s into str

	/* What should you do if the q is NULL? */
	/* What if either call to malloc returns NULL? */
	newh->value = str;	    	    
	if (q->head == NULL){
		//if queue is empty
		newh->next = q->head;	    
		q->head = newh;
		q->tail = newh;
		q->size ++;
	} else {
		//case for existing queue
		newh->next = q->head;	    
		q->head = newh;	    
		q->size++;
	}		

	return true;
}


/*
   Attempt to insert element at tail of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
   */
bool q_insert_tail(queue_t *q, char *s){
	/* You need to write the complete code for this function */
	/* Remember: It should operate in O(1) time */

	list_ele_t *newt;
	char *str;

	if (q == NULL){
		return false;
	}

	//allocating space for the node and the string
	newt = malloc(sizeof(list_ele_t));
	if (newt == NULL){
		return false;
	}
	str = malloc(strlen(s)+1);
	if (str == NULL){
		free(newt);
		return false;
	}
	strcpy(str, s);
	//if the queue, new node or string returned null, insert was a failure
	//and you need to free the that had been previously allocated
	newt->value = str;
	if (q->head == NULL){
		//if queue is empty adding to the tail is the same process
		//as adding to the head
		newt->next = q->head;
		q->head = newt;
		q->tail = newt;
		q->size ++;
	} else {
		q->tracker = q->tail;
		newt->next = NULL;
		q->tracker->next = newt;
		q->tail = newt; //make the node the new tail reference
		q->size ++;
				
	}
	return true;
}

/*
   Attempt to remove element from head of queue.
   Return true if successful.
   Return false if queue is NULL or empty.
   If sp is non-NULL and an element is removed, copy the removed string to *sp
   (up to a maximum of bufsize-1 characters, plus a null terminator.)
   The space used by the list element and the string should be freed.
   */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
	/* You need to fix up this code. */
	if (q == NULL || q->size == 0){
		return false;
	} else {
		if (sp != NULL){
			strncpy(sp, (q->head->value), (bufsize-1));
			sp[bufsize-1] = '\0';
			q->tracker = q->head;
			//make head reference the next element (remove head)
			q->head = q->head->next;
			free(q->tracker->value);
			free(q->tracker);
			//free the string and the space of the removed string
			q->size --; //decrement the size of the queue
		}
	}
	return true;
}

/*
   Return number of elements in queue.
   Return 0 if q is NULL or empty
   */
int q_size(queue_t *q)
{
	/* You need to write the code for this function */
	/* Remember: It should operate in O(1) time */
	if (q == NULL){
		return 0;
	} else {
		return q->size;
	}
}

/*
   Reverse elements in queue
   No effect if q is NULL or empty
   This function should not allocate or free any list elements
   (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
   It should rearrange the existing ones.
   */
void q_reverse(queue_t *q)
{
	/* You need to write the code for this function */
	if (q != NULL && q->size != 0){
		q->prev = NULL;
		q->tracker = q->head;
		q->flipped = q->head;
		q->fwd = NULL;
		while (q->tracker != NULL){
			q->fwd = q->tracker->next;
			q->tracker->next = q->prev;
			q->prev = q->tracker;
			q->tracker = q->fwd;
		}
		q->head = q->prev; //finish the reversing
		q->tail = q->flipped;//new tail reference (was the original head)
	}	
}
