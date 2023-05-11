#include "./dictionary/dictionary.h"

#define SEARCH_WORD 1
#define INSERT_WORD 2
#define DELETE_WORD 3
#define SHOW_NODE   4
#define SHOW_TREE   5
#define EXIT        6

void show_menu();
void select_option(int option);

char word[50];
Dict* dict;

int main() {
  AVLTree* tree = newAVLTree();
  char letras[] = {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'x',
    'z'
  };

  for (int i = 0; i < 24; i++) {
    tree_insert(tree, letras[i]);
  }

  tree_remove(tree, 'q');
  tree_remove(tree, 'u');
  tree_remove(tree, 'h');


  tree_preorder_walk(tree->root);



  // dict = newDict();
  // unsigned char option;

  // scanf("%d", &option);

  // printf("Todas os dados foram carregados com sucesso!!");
  // select_option(option);
  
  // while (true) {
  //   show_menu();

  //   scanf("%d", &option);
  //   printf("%d\n", option);

  //   if (option == 6) {
  //     printf("Programa Encerrado!!\n");
  //     exit(0);
  //   }

  //   select_option(option);
  // }

  return 0;
}

void show_menu() {
  printf("\n*** MENU DE OPÇÕES: ENTRE COM A OPÇÃO DESEJADA ***\n\n");
  printf("1. Busca\n");
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
      char letter;
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
