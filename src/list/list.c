#include "./list.h"

List* newList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = (ListNode*) malloc(sizeof(ListNode));
    list->head->prev = list->head;
    list->head->next = list->head;
    return list;
}

static ListNode* search_in(List* list, char* word) {
    strcpy(list->head->word, word);
    ListNode* current = list->head->next;

    while (strcmp(current->word, word) < 0) {
        current = current->next;
    }

    return current;
}

bool is_word_in(List* list, char* word) {
    strcpy(list->head->word, word);
    ListNode* current = list->head->next;

    while (strcmp(current->word, word) != 0) {
        current = current->next;
    }

    return current != list->head;
}

void insert_in(List* list, char* word) {
    ListNode* current = search_in(list, word);
    bool word_not_found = (
        current == list->head || strcmp(current->word, word) != 0);

    if (word_not_found) {
        ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
        strcpy(new_node->word, word);
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    }
}

void remove_from(List* list, char* word) {
    ListNode* current = search_in(list, word);
    bool word_found = (
        current != list->head && strcmp(current->word, word) == 0);

    if (word_found) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    }
}

void print_list(List* list) {
    ListNode* current = list->head->next;

    printf("[ ");
    while (current != list->head) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("]\n");
}