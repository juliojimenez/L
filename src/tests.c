#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "liststruct.h"
#include "reader.h"
#include "writer.h"
#include "eval.h"

void test_0000_lexer() {
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

    printf("[0000] test_lexer passed\n");
}

void test_0001_reader() {
    char input[] = "(foo (bar) baz)";
    void* result = read(input);

    Pair* list = (Pair*)result;
    assert(strcmp((char*)list->car, "foo") == 0);
    Pair* rest = (Pair*)list->cdr;
    Pair* inner_list = (Pair*)rest->car;
    assert(istext(inner_list));
    assert(strcmp((char*)inner_list->car, "bar") == 0);

    printf("[0001] test_reader passed\n");
}

void test_0002_writer() {
    char input[] = "(foo (bar) baz)";
    void* result = read(input);
    print(result);

    printf("[0002] test_writer passed\n");
}

void test_0003_addition() {
    char input[] = "(+ 1 2)";
    void* result = read(input);
    eval(result);
    assert(strcmp(ret, "3") == 0);

    printf("[0003] test_addition passed\n");
}

void test_0004_subtraction() {
    char input[] = "(- 2 1)";
    void* result = read(input);
    eval(result);
    assert(strcmp(ret, "1") == 0);

    printf("[0004] test_subtraction passed\n");
}

void test_0005_multiplication() {
    char input[] = "(* 2 3)";
    void* result = read(input);
    eval(result);
    assert(strcmp(ret, "6") == 0);

    printf("[0005] test_multiplication passed\n");
}

int main() {
    test_0000_lexer();
    test_0001_reader();
    test_0002_writer();
    test_0003_addition();
    test_0004_subtraction();
    test_0005_multiplication();
    return 0;
}
