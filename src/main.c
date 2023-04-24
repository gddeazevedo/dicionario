#include "./avl_tree/avl_tree.h"

void main() {
  AVLTree* t = newAVLTree();
  tree_insert(t, 'o');
  tree_insert(t, 'g');
  tree_insert(t, 'v');
  tree_insert(t, 'c');
  tree_insert(t, 'e');
  tree_insert(t, 'b');
  tree_insert(t, 'a');
  tree_insert(t, 'h');
  tree_insert(t, 'u');
  tree_insert(t, 'z');
  tree_insert(t, 'f');
  tree_insert(t, 'm');
  tree_insert(t, 'n');

  tree_remove(t, 'f');
  tree_remove(t, 'e');
  tree_remove(t, 'b');
  // tree_remove(t, 'o');
  // tree_remove(t, 'g');


  printf("Preorder: ");
  tree_preorder_walk(t->root);
  printf("\nIn Order: ");
  tree_inorder_walk(t->root);
  printf("\nRoot: %c\nRoot height: %d\n", t->root->key, t->root->height);
}
