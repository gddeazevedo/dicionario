#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SEARCH_WORD 1
#define INSERT_WORD 2
#define DELETE_WORD 3
#define SHOW_NODE   4
#define SHOW_TREE   5
#define EXIT        6


// ################# LIST CODE #####################
typedef struct __list_node {
	char word[100];
	struct __list_node* prev;
	struct __list_node* next;
} ListNode;

typedef struct __linked {
	ListNode* head;
	unsigned int size;
} List;

List* newList();
ListNode* list_search(List* list, char* word);
bool list_insert(List* list, char* word);
bool list_remove(List* list, char* word);
void list_print(List* list);
void list_print_v2(List* list);
void list_clear(List* list);
void delete_list(List* list);


// ################# AVL TREE CODE #####################
typedef struct __avl_node {
  char key;
  List* words;
  int height;
  int bf; // balance factor
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
AVLNode* tree_maximum(AVLNode* root);
AVLNode* tree_successor(AVLNode* node);
AVLNode* tree_predecessor(AVLNode* node);

void tree_preorder_walk(AVLNode* root);
void tree_inorder_walk(AVLNode* root);
void tree_insert(AVLTree* tree, char key);
void transplant(AVLTree* tree, AVLNode* u, AVLNode* v);
void tree_remove(AVLTree* tree, char key);
void right_rotate(AVLTree* tree, AVLNode* node);
void left_rotate(AVLTree* tree, AVLNode* node);
void update_heights_and_bf(AVLNode* node);
void balance(AVLTree* tree, AVLNode* node);
void fixup(AVLTree* tree, AVLNode* node);

int max(int x, int y);
int get_avlnode_height(AVLNode* node);
int get_avlnode_level(AVLNode* node);


// ################# DICT CODE #####################
typedef struct __dict {
  AVLTree* tree;
  int total_words;
} Dict;

Dict* newDict();
void dict_search(Dict* dict, char* word);
void dict_insert(Dict* dict, char* word);
void dict_remove(Dict* dict, char* word);
void dict_show_words_with(Dict* dict, char letter);
void dict_show_all_words(Dict* dict);

// ######### IO HELPERS #########
void show_menu();
void select_option(int option);

char word[50];
Dict* dict;

int main() {
  dict = newDict();
  unsigned int option;

  scanf("%d", &option);

  printf("Todos os dados foram carregados com sucesso!!");
  select_option(option);
  
  while (true) {
    show_menu();

    scanf("%d", &option);
    printf("%d\n", option);

    if (option == 6) {
      printf("Programa Encerrado!!\n");
      exit(0);
    }

    select_option(option);
  }

  return 0;
}


// ############## LIST FUNCTIONS ##################
List* newList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = (ListNode*) malloc(sizeof(ListNode));
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
    return list;
}

ListNode* list_search(List* list, char* word) {
    strcpy(list->head->word, word);
    ListNode* current = list->head->next;

    while (strcmp(current->word, word) < 0) {
        current = current->next;
    }

    return current;
}

bool list_insert(List* list, char* word) {
    ListNode* current = list_search(list, word);
    bool word_not_found = (
        current == list->head || strcmp(current->word, word) != 0);

    if (word_not_found) {
        ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
        strcpy(new_node->word, word);
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
        list->size += 1;
        return true;
    }

    return false;
}

bool list_remove(List* list, char* word) {
    ListNode* current = list_search(list, word);
    bool word_found = (
        current != list->head && strcmp(current->word, word) == 0);

    if (word_found) {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        list->size -= 1;
        return true;
    }

    return false;
}

void list_print(List* list) {
    ListNode* current = list->head->next;

    printf("[ ");
    while (current != list->head) {
        if (current->next != list->head)
            printf("%s, ", current->word);
        else
            printf("%s ", current->word);
        current = current->next;
    }
    printf("]\n");
}

void list_print_v2(List* list) {
  ListNode* current = list->head->next;

  while (current != list->head) {
      printf("%s\n", current->word);
      current = current->next;
  }
}

void list_clear(List* list) {
  ListNode* current = list->head->next;
  ListNode* aux = NULL;

  while (current != list->head) {
    aux = current->next;
    free(current);
    current = aux;
  }

  list->head->next = list->head;
  list->head->prev = list->head;
}

void delete_list(List* list) {
  list_clear(list);
  free(list->head);
  list->head = NULL;
}

// ############## AVL TREE FUNCTIONS ##################
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

AVLNode* tree_maximum(AVLNode* root) {
  while (root->right != NULL) {
    root = root->right;
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

AVLNode* tree_predecessor(AVLNode* node) {
  if (node->left != NULL) {
    return tree_maximum(node->left);
  }

  AVLNode* aux = node->parent;

  while (aux != NULL && node == aux->left) {
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
    AVLNode* y = tree_predecessor(z);
    AVLNode* y_parent = y->parent;

    if (y->parent != z) {
      transplant(tree, y, y->left);
      y->left = z->left;
      y->left->parent = y;
    }

    transplant(tree, z, y);
    y->right = z->right;
    y->right->parent = y;

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

// ############### DICT FUNCTIONS ###################
Dict* newDict() {
  Dict* d = (Dict*) malloc(sizeof(Dict));
  d->tree = newAVLTree();
  d->total_words = 0;
  return d;
}

void dict_search(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("Palavra Inexistente!\n");
    return;
  }

  ListNode* list_node = list_search(node->words, word);

  if (list_node == node->words->head || strcmp(word, list_node->word) != 0) {
    printf("Palavra Inexistente!\n");
    return;
  }

  int level = get_avlnode_level(node);

  printf("A Palavra \'%s\' foi encontrada no NÓ \'%c\' nível %d\n", word, node->key, level);
}

void dict_insert(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    tree_insert(dict->tree, letter);
    node = tree_search(dict->tree->root, letter);
  }

  if (list_insert(node->words, word)) dict->total_words += 1;
}

void dict_remove(Dict* dict, char* word) {
  char letter = word[0];
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node == NULL) {
    printf("A Palavra \'%s\' não consta no Dicionário\n", word);
    return;
  }

  if (list_remove(node->words, word)) {
    printf(
      "A palavra \'%s\' foi Excluída com sucesso do NÓ \'%c\' nível %d\n",
      word, node->key, get_avlnode_level(node)  
    );

    if (node->words->size == 0) {
      tree_remove(dict->tree, letter);
    }
  } else {
    printf("A Palavra \'%s\' não consta no Dicionário\n", word);
  }
}

void dict_show_words_with(Dict* dict, char letter) {
  AVLNode* node = tree_search(dict->tree->root, letter);

  if (node != NULL) {
    printf(
      "\nA(s) Palavra(s) contida(s) no NÓ \'%c\' nível %d são:\n\n",
      node->key, get_avlnode_level(node)
    );
    list_print_v2(node->words);
  } else {
    printf("\nO NÓ %c não se encontra na AVL\n", letter);
  }
}

void dict_show_all_words(Dict* dict) {
  tree_inorder_walk(dict->tree->root);
}

// ############## IO HELPERS ###################
void show_menu() {
  printf("\n*** MENU DE OPÇÕES: ENTRE COM A OPÇÃO DESEJADA ***\n\n");
  printf("1. Pesquisa\n");
  printf("2. Inserção\n");
  printf("3. Remoção\n");
  printf("4. Impressão de um nó\n");
  printf("5. Impressão da árvore\n");
  printf("6. Encerrar\n\n");
}

void select_option(int option) {
  dict->total_words = 0;

  switch (option) {
    case SEARCH_WORD:
      printf("Informe a palavra a ser Pesquisada:\n\n");
      scanf("%s", word);
      printf("%s\n", word);
      dict_search(dict, word);
      break;
    case INSERT_WORD:
      while (true) {
        scanf("%s", word);
        if (strcmp(word, "0") == 0) break;
        dict_insert(dict, word);
      }
      printf("\nTotal de %d palavras inseridas no dicionário\n", dict->total_words);
      break;
    case DELETE_WORD:
      printf("Informe a palavra que deseja Excluir:\n\n");
      scanf("%s", word);
      printf("%s\n\n", word);
      dict_remove(dict, word);
      break;
    case SHOW_NODE:
      printf("Informe o nó que deseja Imprimir:\n\n");
      scanf("%s", word);
      printf("%c\n", word[0]);
      dict_show_words_with(dict, word[0]);
      break;
    case SHOW_TREE:
      printf("Imprimindo Árvore...\n");
      dict_show_all_words(dict);
      break;
    default:
      exit(0);
  }
}
