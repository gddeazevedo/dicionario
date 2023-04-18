#include "avl_tree.h"

AVLTree* newAVLTree() {
  AVLTree* tree = (AVLTree*) malloc(sizeof(AVLTree));
  tree->root = NULL;
  return tree;
}

AVLNode* newAVLNode(char key) {
  AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
  node->parent = NULL;
  node->left   = NULL;
  node->right  = NULL;
  node->key = key;
  return node;
}

AVLNode* tree_search(AVLNode* root, char key) {
    while (root != NULL && key != root->key) {
        root = (key < root->key) ? root->left : root->right;
    }

    return root;
}

AVLNode* tree_minimum(AVLNode* root) {
  while (root->left != NULL) {
    root = root->left;
  }

  return root;
}

AVLNode* tree_successor(AVLNode* node) {
  if (node->right != NULL) {
    return tree_minimum(node->right);
  }

  AVLNode* aux = node->parent;

  while (aux != NULL && node == aux->right) {
    node = aux;
    aux = aux->parent;
  }

  return aux;
}

void tree_preorder_walk(AVLNode* root) {
  if (root == NULL) return;
  printf("%c ", root->key);
  tree_preorder_walk(root->left);
  tree_preorder_walk(root->right);
}

void tree_inorder_walk(AVLNode* root) {
  if (root == NULL) return;
  tree_inorder_walk(root->left);
  printf("%c ", root->key);
  tree_inorder_walk(root->right);
}

void tree_insert(AVLTree* tree, char key) {
  AVLNode* y = NULL;
  AVLNode* x = tree->root;
  AVLNode* z = newAVLNode(key);

  if (tree_search(tree->root, key) != NULL) return;

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

void transplant(AVLTree* tree, AVLNode* u, AVLNode* v) {
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

void tree_remove(AVLTree* tree, char key) {
  AVLNode* z = tree_search(tree->root, key);

  if (z == NULL) return;

  if (z->left == NULL) {
    transplant(tree, z, z->right);
  } else if (z->right == NULL) {
    transplant(tree, z, z->left);
  } else {
    AVLNode* y = tree_successor(z);

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

void right_rotate(AVLTree* tree, AVLNode* node) {
  AVLNode* aux = node->left;
  node->left = aux->right;

  if (aux->right != NULL) {
    aux->right->parent = node;
  }

  aux->parent = node->parent;

  if (node->parent == NULL) {
    tree->root = aux;
  } else if (node == node->parent->left) {
    node->parent->left = aux;
  } else {
    node->parent->right = aux;
  }

  aux->right = node;
  node->parent = aux;
}

void left_rotate(AVLTree* tree, AVLNode* node) {
  AVLNode* aux = node->right;
  node->right = aux->left;

  if (aux->left != NULL) {
    aux->left->parent = node;
  }

  aux->parent = node->parent;

  if (node->parent == NULL) {
    tree->root = aux;
  } else if (node == node->parent->left) {
    node->parent->left = aux;
  } else {
    node->parent->right = aux;
  }

  aux->left = node;
  node->parent = aux;
}
