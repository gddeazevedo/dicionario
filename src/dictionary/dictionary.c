#include "./dictionary.h"

Dict* newDict() {
  Dict* d = (Dict*) malloc(sizeof(Dict));
  d->tree = newAVLTree();
  return d;
}

bool search_word(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) return false;
  if (list_search(node->words, word) == node->words->head) return false;

  return true;
}

void insert_word(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    tree_insert(dict->tree, letter);
    node = tree_search(dict->tree->root, letter);
  }

  list_insert(node->words, word);
}

void remove_word(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("Não há nenhuma palavra com a letra \'%c\' registrada no dicionário\n", letter);
    return;
  }

  if (list_remove(node->words, word)) {
    printf("A palavra \'%s\' foi removida com sucesso!\n", word);

    if (node->words->size == 0) {
      tree_remove(dict->tree, letter);
    }
  } else {
    printf("%s não está no dicionário\n", word);
  }
}

void show_words_with(Dict* dict, char letter) {
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node != NULL) {
    printf("%c: ", letter);
    list_print(node->words);
  } else {
    printf("No words with letter \"%c\"\n", letter);
  }
}
