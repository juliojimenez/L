#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "liststruct.h"
#include "reader.h"

void test_lexer() {
    char* input = "(foo (bar) baz)";
    int token_count = lexer(input);
    assert(token_count == 13);
    assert(strcmp(token[0], "(") == 0);
    assert(strcmp(token[1], "f") == 0);
    assert(strcmp(token[2], "o") == 0);
    assert(strcmp(token[3], "o") == 0);
    assert(strcmp(token[4], "(") == 0);
    assert(strcmp(token[5], "b") == 0);
    assert(strcmp(token[6], "a") == 0);
    assert(strcmp(token[7], "r") == 0);
    assert(strcmp(token[8], ")") == 0);
    assert(strcmp(token[9], "b") == 0);
    assert(strcmp(token[10], "a") == 0);
    assert(strcmp(token[11], "z") == 0);
    assert(strcmp(token[12], ")") == 0);
    printf("test_lexer passed\n");
}

void test_reader() {
    char input[] = "(foo (bar) baz)";
    void* result = read(input);

    Pair* list = (Pair*)result;
    assert(strcmp((char*)list->car, "f") == 0);
    Pair* rest = (Pair*)list->cdr;
    Pair* inner_list = (Pair*)rest->car;
    assert(ispair(inner_list) == 0);

    printf("test_reader passed\n");
}

int main() {
    test_lexer();
    test_reader();
    return 0;
}
