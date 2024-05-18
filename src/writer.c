#include <stdio.h>
#include "liststruct.h"

void print_exp(void* exp);

void print_list(Pair* list) {
    if (list->cdr == NULL) {
        print_exp(list->car);
        printf(")");
    } else {
        print_exp(list->car);
        printf(" ");
        print_list(list->cdr);
    }
}

void print_exp(void* exp) {
    if (ispair(exp)) {
        printf("(");
        print_list(exp);
    } else {
        printf("%s", (char*)exp);
    }
}

void print(void* exp) {
    print_exp(exp);
    printf("\n");
}
