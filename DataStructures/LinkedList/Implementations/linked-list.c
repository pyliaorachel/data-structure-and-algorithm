#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value; // holding the value of the node; can be any type or have multiple value fields
	struct Node *next; // pointing to the next node in list
};

typedef struct Node Node;

struct SinglyLinkedList {
	Node *head; // pointing to the first node in list
	int size; // count of nodes in list; optional field
};

typedef struct SinglyLinkedList SinglyLinkedList;

int main() {
	// create an empty SinglyLinkedList
	SinglyLinkedList *list = NULL;
	// declare pointer n to hold nodes; temp_n to point to temporary nodes in list (a cursor)
	Node *n = NULL;
	Node *temp_n = NULL;
	// initialize list
	list = malloc(sizeof(SinglyLinkedList));
	list->head = NULL;
	list->size = 0;

	/* Example 1 - add a node to the list; remove a node from the list */
	
	// create a node
	n = malloc(sizeof(Node));
	n->value = 1; // give the node a value
	n->next = NULL; // the node is not linked by other nodes yet
	
	// add it to the head of the list
	list->head = n;
	list->size++;

	// remove it from the list
	list->head = NULL;
	list->size--;

	// destroy it by releasing its memory
	free(n);

	/* Example 2 - add multiple nodes to the list */

	// declare pointer temp_n to point to the head of the empty list
	temp_n = list->head;

	for (int i = 0; i < 1000; i++) {
		// create new node
		n = malloc(sizeof(Node));
		n->value = i;
		n->next = NULL;

		// add to the head of the list
		if (list->head == NULL) { // if list empty, let head point to n
			list->head = n;
		} else { // else let the currently pointed node link to n (by assigning *next to point to n)
			temp_n->next = n;
		}
		temp_n = n;
		list->size++;
	}

	/* Example 3 - list traversal (summing values in list) */
	int sum = 0;
	temp_n = list->head;

	while (temp_n != NULL) {
		printf("value: %d\n", temp_n->value);
		sum += temp_n->value;
		temp_n = temp_n->next; // move forward the cursor
	}

	printf("sum: %d\n", sum);

	/* Example 4 - insert node into list */
	int index = 5; // inserting into index 5 of list
	n = malloc(sizeof(Node));
	n->value = 87;
	n->next = NULL;

	// traverse through the list to find index; assume we don't check if index is valid
	temp_n = list->head;

	for (int i = 0; i < index-1; i++) {
		temp_n = temp_n->next;
	}

	// insert by moving around pointers
	n->next = temp_n->next;
	temp_n->next = n;

	list->size++;

	/* Example 5 - remove node from list */
	index = 5; // removing node at index 5 of list

	// traverse through the list to find index; assume we don't check if index is valid
	temp_n = list->head;

	for (int i = 0; i < index-1; i++) {
		temp_n = temp_n->next;
	}

	// remove by moving around pointers; notice that we're removing temp_n->next instead of temp->n
	n = temp_n->next; // n = node to remove
	temp_n->next = n->next; // connect the previous node and the next node
	free(n); // release memory

	list->size--;	

	/* Example 6 - destroy list (freeing all memories of nodes) */

	while (list->head != NULL) {
		temp_n = list->head;
		list->head = list->head->next;
		free(temp_n);
	}

	// finally, free list as well
	free(list);

	return 0;
}