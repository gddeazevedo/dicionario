#include "./dictionary/dictionary.h"
#include <time.h>

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
  dict = newDict();
  unsigned char option;

  clock_t begin = clock();

  scanf("%d", &option);

  select_option(option);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("\nEXECUTION TIME: %f\n", time_spent);

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
