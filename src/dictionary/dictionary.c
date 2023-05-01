#include "./dictionary.h"

Dict* newDict() {
  Dict* d = (Dict*) malloc(sizeof(Dict));
  d->tree = newAVLTree();
  return d;
}

void dict_search(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("Palavra Inexistente\n");
    return;
  };

  ListNode* list_node = list_search(node->words, word);

  if (list_node == node->words->head || strcmp(word, list_node->word) != 0) {
    printf("Palavra Inexistente!\n");
    return;
  }

  int level = get_avlnode_level(node);

  printf("A Palavra %s foi encontrada no NÓ \'%c\' nível %d\n", word, node->key, level);
}

void dict_insert(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    tree_insert(dict->tree, letter);
    node = tree_search(dict->tree->root, letter);
  }

  list_insert(node->words, word);
  dict->total_words += 1;
}

void dict_remove(Dict* dict, char* word) {
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

    dict->total_words -= 1;
  } else {
    printf("A palavra \'%s\' não está no dicionário\n", word);
  }
}

void dict_show_words_with(Dict* dict, char letter) {
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node != NULL) {
    printf("%c: ", letter);
    list_print(node->words);
  } else {
    printf("No words with letter \"%c\"\n", letter);
  }
}

void dict_show_all_words(Dict* dict) {
  tree_inorder_walk(dict->tree->root);
}
