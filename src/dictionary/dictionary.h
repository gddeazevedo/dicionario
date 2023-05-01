#ifndef __dictionary_h
#define __dictionary_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../avl_tree/avl_tree.h"


typedef struct __dict {
  AVLTree* tree;
  unsigned int total_words;
} Dict;


Dict* newDict();
void dict_search(Dict* dict, char* word);
void dict_insert(Dict* dict, char* word);
void dict_remove(Dict* dict, char* word);
void dict_show_words_with(Dict* dict, char letter);
void dict_show_all_words(Dict* dict);

#endif
