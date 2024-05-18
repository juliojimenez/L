#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "liststruct.h"
#include "reader.h"

void test_lexer() {
    char* input = "(foo (bar) baz)";
    int token_count = lexer(input);
    assert(token_count == 7);
    assert(strcmp(token[0], "(") == 0);
    assert(strcmp(token[1], "foo") == 0);
    assert(strcmp(token[2], "(") == 0);
    assert(strcmp(token[3], "bar") == 0);
    assert(strcmp(token[4], ")") == 0);
    assert(strcmp(token[5], "baz") == 0);
    assert(strcmp(token[6], ")") == 0);
    printf("test_lexer passed\n");
}

void test_reader() {
    char input[] = "(foo (bar) baz)";
    void* result = read(input);

    Pair* list = (Pair*)result;
    assert(strcmp((char*)list->car, "foo") == 0);
    Pair* rest = (Pair*)list->cdr;
    Pair* inner_list = (Pair*)rest->car;
    assert(ispair(inner_list));
    assert(strcmp((char*)inner_list->car, "bar") == 0);

    printf("test_reader passed\n");
}

int main() {
    test_lexer();
    test_reader();
    return 0;
}
