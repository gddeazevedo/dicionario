#ifndef __list_h
#define __list_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct __list_node {
	char word[100];
	struct __list_node* prev;
	struct __list_node* next;
} ListNode;

typedef struct __linked {
	ListNode* head;
} List;


List* newList();
static ListNode* search_in(List* list, char* word);
bool is_word_in(List* list, char* word);
void insert_in(List* list, char* word);
void remove_from(List* list, char* word);
void print_list(List* list);



#endif
