#include "./dictionary/dictionary.h"

void main() {
  Dict* dict = newDict();
  insert_word(dict, "banana");
  insert_word(dict, "ameixa");
  insert_word(dict, "pamonha");
  insert_word(dict, "alecrim");
  insert_word(dict, "zumba");
  insert_word(dict, "bala");
  insert_word(dict, "aladin");
  insert_word(dict, "pasta");
  insert_word(dict, "vestido");
  insert_word(dict, "canivete");
  insert_word(dict, "helicoptero");
  insert_word(dict, "material");
  insert_word(dict, "utopia");
  insert_word(dict, "will");
  insert_word(dict, "xerox");
  insert_word(dict, "yellow");
  insert_word(dict, "navio");
  insert_word(dict, "lupa");
  insert_word(dict, "otorrinolaringologista");
  insert_word(dict, "olho");
  insert_word(dict, "repolho");
  insert_word(dict, "quasar");
  insert_word(dict, "sapo");
  insert_word(dict, "danone");
  insert_word(dict, "elefante");
  insert_word(dict, "faca");
  insert_word(dict, "fazer");
  insert_word(dict, "folha");
  insert_word(dict, "lapis");

  printf("----Preorder----\n");
  tree_preorder_walk(dict->tree->root);
  printf("\n----In Order----\n");
  tree_inorder_walk(dict->tree->root);
  printf("\nRoot: %c\nRoot height: %d\n", dict->tree->root->key, dict->tree->root->height);
}
