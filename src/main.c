#include "./dictionary/dictionary.h"

void show_menu();

int main() {
  char word[50];
  unsigned char option;
  Dict* dict = newDict();

  while (true) {
    scanf("%s", word);
    if (strcmp(word, "0") == 0) break;
    dict_insert(dict, word);
  }

  printf("Todas os dados foram carregados com sucesso!!\n");
  printf("Total de %d palavras inseridas no dicionário\n", dict->total_words);

  while (true) {
    show_menu();

    scanf("%d", &option);
    printf("%d\n", option);

    if (option == 6) {
        printf("Programa Encerrado!!\n");
        break;
    };

    switch (option) {
      case 1:
        printf("Informe a palavra a ser Pesquisada:\n\n");
        scanf("%s", word);
        printf("%s\n", word);
        dict_search(dict, word);
        break;
      case 2:
        // inserção
        break;
      case 3:
        // remoção
        break;
      case 4:
        // impressao de um nó
        break;
      case 5:
        printf("Imprimindo Árvore...\n");
        dict_show_all_words(dict);
        break;
      default:
        break;
    }
  }

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
