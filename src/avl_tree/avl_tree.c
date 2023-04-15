#include "avl_tree.h"

Tree* newTree() {
  Tree* tree = (Tree*) malloc(sizeof(Tree));
  tree->root = NULL;
  return tree;
}

Node* newNode(char key) {
  Node* node = (Node*) malloc(sizeof(Node));
  node->parent = NULL;
  node->left   = NULL;
  node->right  = NULL;
  node->key = key;
  return node;
}

void tree_preorder_walk(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->key);
    tree_preorder_walk(root->left);
    tree_preorder_walk(root->right);
}

Node* tree_search(Node* root, char key) {
    while (root != NULL && key != root->key) {
        root = (key < root->key) ? root->left : root->right;
    }

    return root;
}

Node* tree_minimum(Node* root) {
  while (root->left != NULL) {
    root = root->left;
  }

  return root;
}

Node* tree_successor(Node* node) {
  if (node->right != NULL) {
    return tree_minimum(node->right);
  }

  Node* aux = node->parent;

  while (aux != NULL && node == aux->right) {
    node = aux;
    aux = aux->parent;
  }
}

void tree_insert(Tree* tree, char key) {
  Node* y = NULL;
  Node* x = tree->root;
  Node* z = newNode(key);

  while (x != NULL) {
    y = x;
    x = (z->key < x->key) ? x->left : x->right;
  }

  z->parent = y;

  if (y == NULL) {
    tree->root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
}

void transplant(Tree* tree, Node* u, Node* v) {
  if (u->parent == NULL) {
    tree->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  if (v != NULL) {
    v->parent = u->parent;
  }
}

void tree_remove(Tree* tree, char key) {
  Node* z = tree_search(tree->root, key);

  if (z == NULL) return;

  if (z->left == NULL) {
    transplant(tree, z, z->right);
  } else if (z->right == NULL) {
    transplant(tree, z, z->left);
  } else {
    Node* y = tree_successor(z);

    if (y->parent != z) {
      transplant(tree, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;
  }

  free(z);
}
