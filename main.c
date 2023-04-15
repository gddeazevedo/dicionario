#include "./src/avl_tree/avl_tree.h"

void main() {
  Tree* t = newTree();
  tree_insert(t, 'g');
  tree_insert(t, 'b');
  tree_insert(t, 'm');
  tree_insert(t, 'a');
  tree_insert(t, 'c');
  tree_insert(t, 'j');
  tree_insert(t, 'o');
  tree_insert(t, 'n');
  tree_remove(t, 'g');
  tree_remove(t, 'b');
  tree_remove(t, 'm');

  tree_preorder_walk(t->root);
}
