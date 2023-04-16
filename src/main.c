#include "./avl_tree/avl_tree.h"

void main() {
  // List* l = newList();
  //
  // list_insert(l, "zaratustra");
  // list_insert(l, "banana");
  // list_insert(l, "abacate");
  // list_insert(l, "peixe");
  // list_remove(l, "banana");

  Tree* t = newTree();
  tree_insert(t, 'g');
  tree_insert(t, 'b');
  tree_insert(t, 'm');
  tree_insert(t, 'a');
  tree_insert(t, 'c');
  tree_insert(t, 'j');
  tree_insert(t, 'o');
  tree_insert(t, 'n');

  right_rotate(t, tree_search(t->root, 'o'));
  left_rotate(t, t->root);
  left_rotate(t, t->root);


  tree_preorder_walk(t->root);
  printf("\nRoot: %c\n", t->root->key);
  // list_print(l);
}
