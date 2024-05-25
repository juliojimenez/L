#include <stdio.h>
#include "environment.h"
#include "liststruct.h"

void print_exp(void* exp);

void print_cons(Pair* pair) {
    print_exp(pair->car);
    printf(" . ");
    print_exp(pair->cdr);
}

void print_list(Pair* list) {
    if (list->cdr == NULL) {
        print_exp(list->car);
        printf(")");
    } else {
        if (!islist(list->cdr) && !istext(list->cdr) && list->cdr != NULL) {
            print_cons(list);
            printf(")");
        } else {
            print_exp(list->car);
            printf(" ");
            print_list(list->cdr);
        }
    }
}

void print_exp(void* exp) {
    if (istext(exp) || islist(exp)) {
        Pair* pair = exp;
        if (isenv(pair->car)) {
            printf("#<lambda>");
            return;
        } else if (!istext(pair->cdr) && !islist(pair->cdr) && pair->cdr != NULL) {
            printf("(");
            print_cons(exp);
            printf(")");
        } else {
            printf("(");
            print_list(exp);
        }
    } else {
        printf("%s", exp ? (char*)exp : "()");
    }
}

void print(void* exp) {
    print_exp(exp);
    printf("\n");
}
