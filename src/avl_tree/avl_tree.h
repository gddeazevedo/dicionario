#ifndef __avl_tree_h
#define __avl_tree_h

#include <stdlib.h>
#include <stdio.h>
#include "../list/list.h"

typedef struct __avl_node {
  char key;
  int height;
  struct __avl_node* parent;
  struct __avl_node* left;
  struct __avl_node* right;
} AVLNode;

typedef struct __avl_tree {
  AVLNode* root;
} AVLTree;

AVLTree* newAVLTree();
AVLNode* newAVLNode(char key);
AVLNode* tree_search(AVLNode* root, char key);
AVLNode* tree_minimum(AVLNode* root);
AVLNode* tree_successor(AVLNode* node);

void tree_preorder_walk(AVLNode* root);
void tree_inorder_walk(AVLNode* root);
void tree_insert(AVLTree* tree, char key);
void transplant(AVLTree* tree, AVLNode* u, AVLNode* v);
void tree_remove(AVLTree* tree, char key);
void right_rotate(AVLTree* tree, AVLNode* node);
void left_rotate(AVLTree* tree, AVLNode* node);

#endif
