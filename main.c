#include "./src/list/list.h"

void main() {
    List* list = newList();
    insert_in(list, "paçoca");
    insert_in(list, "amarula");
    insert_in(list, "peixe");
    insert_in(list, "anel");
    insert_in(list, "carteira");
    print_list(list);

    remove_from(list, "carteira");
    remove_from(list, "amarula");
    print_list(list);
}
