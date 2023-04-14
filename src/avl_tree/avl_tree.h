#ifndef __avl_tree_h
#define __avl_tree_h

#include <stdlib.h>
#include <stdio.h>
#include "../list/list.h"

typedef struct __tree_node {
    char letter;
    struct __tree_node* parent;
    struct __tree_node* left;
    struct __tree_node* right;
} TreeNode;

#endif
