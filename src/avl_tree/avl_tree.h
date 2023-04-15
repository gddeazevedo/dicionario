#ifndef __avl_tree_h
#define __avl_tree_h

#include <stdlib.h>
#include <stdio.h>
#include "../list/list.h"

typedef struct __node {
    char key;
    struct __node* parent;
    struct __node* left;
    struct __node* right;
} Node;

typedef struct __tree {
  Node* root;
} Tree;

Tree* newTree();
Node* newNode(char key);
void tree_preorder_walk(Node* root);
Node* tree_search(Node* root, char key);
Node* tree_minimum(Node* root);
Node* tree_maximum(Node* root);
Node* tree_successor(Node* node);
void tree_insert(Tree* tree, char key);
void transplant(Tree* tree, Node* u, Node* v);
void tree_remove(Tree* tree, char key);

#endif
