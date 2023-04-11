#ifndef __linked_list_h
#define __linked_list_h

#include <stdlib.h>
#include <string.h>


typedef struct __list_node {
	char* word;
	struct __list_node* prev;
	struct __list_node* next;
} ListNode;

typedef struct __linked_list {
	ListNode* head;
} LinkedList;


LinkedList* newLinkedList();
ListNode* search_in(LinkedList* list, char* word);
void insert_in(LinkedList* list, char* word);
void remove_from(LinkedList* list, char* word);



#endif
