#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "./dictionary/dictionary.h"


int main() {
    Dict* dict = newDict();
    char word[50];
    time_t start_t;
    time_t end_t;
    double diff_t;

    printf("Starting of the program...\n");
    time(&start_t);

    while (true) {
        scanf("%s", word);
        if (strcmp(word, "0") == 0) break;
        if (strlen(word) <= 2) continue;
        dict_insert(dict, word);
    }

    time(&end_t);
    diff_t = difftime(end_t, start_t);

    printf("%d\n", start_t);
    printf("%d\n", end_t);
    printf("Execution time = %f\n", diff_t);
    printf("Exiting of the program...\n");
    return 0;
}
