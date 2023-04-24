#include "./list.h"

List* newList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = (ListNode*) malloc(sizeof(ListNode));
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
    return list;
}

ListNode* list_search(List* list, char* word) {
    strcpy(list->head->word, word);
    ListNode* current = list->head->next;

    while (strcmp(current->word, word) < 0) {
        current = current->next;
    }

    return current;
}

void list_insert(List* list, char* word) {
    ListNode* current = list_search(list, word);
    bool word_not_found = (
        current == list->head || strcmp(current->word, word) != 0);

    if (word_not_found) {
        ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
        strcpy(new_node->word, word);
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
        list->size += 1;
    }
}

void list_remove(List* list, char* word) {
    ListNode* current = list_search(list, word);
    bool word_found = (
        current != list->head && strcmp(current->word, word) == 0);

    if (word_found) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        list->size -= 1;
    }
}

void list_print(List* list) {
    ListNode* current = list->head->next;

    printf("[ ");
    while (current != list->head) {
        if (current->next != list->head)
            printf("%s, ", current->word);
        else
            printf("%s ", current->word);
        current = current->next;
    }
    printf("]\n");
}
