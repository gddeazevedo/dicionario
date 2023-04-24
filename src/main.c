#include "./dictionary/dictionary.h"

void main() {

  Dict* dict = newDict();
  insert_word(dict, "banana"); // b
  insert_word(dict, "ameixa"); // a
  insert_word(dict, "pamonha"); // p
  insert_word(dict, "alecrim");
  insert_word(dict, "zumba"); // z
  insert_word(dict, "bala");
  insert_word(dict, "aladin");
  insert_word(dict, "pasta");
  insert_word(dict, "vestido"); // v
  insert_word(dict, "canivete"); // c
  insert_word(dict, "helicoptero"); // h
  insert_word(dict, "material");
  insert_word(dict, "utopia");
  insert_word(dict, "will");
  insert_word(dict, "xerox");
  insert_word(dict, "yellow");


  printf("Preorder: ");
  tree_preorder_walk(dict->tree->root);
  printf("\n----In Order----\n");
  tree_inorder_walk(dict->tree->root);
  printf("\nRoot: %c\nRoot height: %d\n", dict->tree->root->key, dict->tree->root->height);
}
