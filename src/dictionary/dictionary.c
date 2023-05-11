#include "./dictionary.h"

Dict* newDict() {
  Dict* d = (Dict*) malloc(sizeof(Dict));
  d->tree = newAVLTree();
  d->total_words = 0;
  return d;
}

void dict_search(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("Palavra Inexistente!\n");
    return;
  }

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

  if (list_insert(node->words, word)) dict->total_words += 1;
}

void dict_remove(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("A Palavra \'%s\' não consta no Dicionário\n", word);
    return;
  }

  if (list_remove(node->words, word)) {
    printf(
      "A palavra \'%s\' foi Excluída com sucesso do NÓ \'%c\' nível %d\n",
      word, node->key, get_avlnode_level(node)  
    );

    if (node->words->size == 0) {
      tree_remove(dict->tree, letter);
    }
  } else {
    printf("A Palavra \'%s\' não consta no Dicionário\n", word);
  }
}

void dict_show_words_with(Dict* dict, char letter) {
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node != NULL) {
    printf(
      "\nA(s) Palavra(s) contida(s) no NÓ \'%c\' nível %d são:\n\n",
      node->key, get_avlnode_level(node)
    );
    list_print_v2(node->words);
  } else {
    printf("\nO NÓ %c não se encontra na AVL\n", letter);
  }
}

void dict_show_all_words(Dict* dict) {
  tree_inorder_walk(dict->tree->root);
}
