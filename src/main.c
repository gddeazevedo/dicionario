#include "./dictionary/dictionary.h"

void show_menu();
void select_option(int option);

char word[50];
Dict* dict;


void main() {
  AVLTree* tree = newAVLTree();
  tree_insert(tree, 'a');
  tree_insert(tree, 'b');
  tree_insert(tree, 'c');
  tree_insert(tree, 'e');
  tree_insert(tree, 'd');
  tree_insert(tree, 'f');
  tree_insert(tree, 'g');
  tree_insert(tree, 'h');
  tree_insert(tree, 'i');
  tree_insert(tree, 'j');
  tree_insert(tree, 'k');
  tree_insert(tree, 'm');

  tree_remove(tree, 'g');
  tree_remove(tree, 'h');
  tree_remove(tree, 'b');
  tree_remove(tree, 'f');
  tree_remove(tree, 'j');
  tree_remove(tree, 'e');



  tree_preorder_walk(tree->root);
}

// int main() {
//   dict = newDict();
//   unsigned char option;

//   while (true) {
//     scanf("%s", word);
//     if (strcmp(word, "0") == 0) break;
//     if (strcmp(word, "2") == 0) continue;
//     dict_insert(dict, word);
//   }

//   printf("Todas os dados foram carregados com sucesso!!\n");
//   printf("Total de %d palavras inseridas no dicionário\n", dict->total_words);

//   while (true) {
//     show_menu();

//     scanf("%d", &option);
//     printf("%d\n", option);

//     if (option == 6) {
//       printf("Programa Encerrado!!\n");
//       break;
//     }

//     select_option(option);
//   }

//   return 0;
// }

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
  switch (option) {
    case 1:
      printf("Informe a palavra a ser Pesquisada:\n\n");
      scanf("%s", word);
      printf("%s\n", word);
      dict_search(dict, word);
      break;
    case 2:
      printf("INSERÇÂO\n");
      break;
    case 3:
      // remoção
      break;
    case 4:
      dict_show_words_with(dict, word[0]);
      break;
    case 5:
      printf("Imprimindo Árvore...\n");
      dict_show_all_words(dict);
      break;
    default:
      break;
  }
}
