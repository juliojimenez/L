#include <stdio.h>
#include "environment.h"
#include "liststruct.h"

void print_exp(void* exp);

void print_cons(Pair* pair) {
    print_exp(pair->car);
    printf(" . ");
    print_exp(pair->cdr);
}

void print_list(Pair* lst) {
    if (lst->cdr == NULL) {
        print_exp(lst->car);
        printf(")");
    } else {
        if (!islist(lst->cdr) && !istext(lst->cdr) && lst->cdr != NULL) {
            print_cons(lst);
            printf(")");
        } else {
            print_exp(lst->car);
            printf(" ");
            print_list(lst->cdr);
        }
    }
}

void print_exp(void* exp) {
    if (istext(exp) || islist(exp)) {
        Pair* pair = exp;
        if (isenv(pair->car)) {
            printf("#<lambda>");
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
