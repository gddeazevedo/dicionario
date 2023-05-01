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
  node->words = newList();
  node->height = 0;
  node->bf = 0;
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

  int level = get_avlnode_level(root);

  if (root->parent != NULL)
    printf(
      "[node: %c, parent: %c, bf: %d, height: %d, level: %d]\n",
      root->key, root->parent->key, root->bf, root->height + 1, level
    );
  else
    printf(
      "[root: %c, bf: %d, height: %d, level: %d]\n",
      root->key, root->bf, root->height + 1, level
    );
  tree_preorder_walk(root->left);
  tree_preorder_walk(root->right);
}

void tree_inorder_walk(AVLNode* root) {
  if (root == NULL) return;
  tree_inorder_walk(root->left);
  int level = get_avlnode_level(root);
  printf("\n- Nó %c nível %d -\n", root->key, level);
  list_print_v2(root->words);
  tree_inorder_walk(root->right);
}

void tree_insert(AVLTree* tree, char key) {
  AVLNode* y = NULL;
  AVLNode* x = tree->root;
  AVLNode* z = newAVLNode(key);

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

  fixup(tree, z->parent);
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
    fixup(tree, z->parent);
  } else if (z->right == NULL) {
    transplant(tree, z, z->left);
    fixup(tree, z->parent);
  } else {
    AVLNode* y = tree_successor(z);
    AVLNode* y_parent = y->parent;

    if (y->parent != z) {
      transplant(tree, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(tree, z, y);
    y->left = z->left;
    y->left->parent = y;

    if (y_parent == z) {
      fixup(tree, y);
    } else {
      fixup(tree, y_parent);
    }
  }

  z->left  = NULL;
  z->right = NULL;
  delete_list(z->words);
  free(z->words);
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

  update_heights_and_bf(node);
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

  update_heights_and_bf(node);
}

void update_heights_and_bf(AVLNode* node) {
  int lh = get_avlnode_height(node->left);
  int rh = get_avlnode_height(node->right);
  node->height = 1 + max(lh, rh);
  node->bf = rh - lh;
}

void balance(AVLTree* tree, AVLNode* node) {
  if (node->bf == -2) {
    if (node->left != NULL && node->left->bf > 0) {
      left_rotate(tree, node->left);
    }
    right_rotate(tree, node);
  } else if (node->bf == 2) {
    if (node->right != NULL && node->right->bf < 0) {
      right_rotate(tree, node->right);
    }
    left_rotate(tree, node);
  }
}

void fixup(AVLTree* tree, AVLNode* node) {
  while (node != NULL) {
    update_heights_and_bf(node);
    balance(tree, node);
    node = node->parent;
  }
}

int max(int x, int y) {
  if (x > y) return x;
  return y;
}

int get_avlnode_height(AVLNode* node) {
  if (node == NULL) return -1;
  return node->height;
}

int get_avlnode_level(AVLNode* node) {
  int level = 0;

  while (node != NULL) {
    level++;
    node = node->parent;
  }

  return level;
}
