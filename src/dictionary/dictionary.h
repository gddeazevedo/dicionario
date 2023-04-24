#ifndef __dictionary_h
#define __dictionary_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../avl_tree/avl_tree.h"


typedef struct __dict {
  AVLTree* tree;
} Dict;


Dict* newDict();
bool search_word(Dict* dict, char* word);
void insert_word(Dict* dict, char* word);
void remove_word(Dict* dict);
void show_words_with(Dict* dict, char letter);

#endif
