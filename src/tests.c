#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "eval.h"
#include "lexer.h"
#include "liststruct.h"
#include "reader.h"
#include "utils.h"
#include "writer.h"

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

    Pair* lst = (Pair*)result;
    assert(strcmp((char*)lst->car, "foo") == 0);
    Pair* rest = (Pair*)lst->cdr;
    Pair* inner_list = (Pair*)rest->car;
    assert(istext(inner_list));
    assert(strcmp((char*)inner_list->car, "bar") == 0);

    printf("[0001] test_reader passed\n");
}

void test_0002_writer() {
    char buffer[256];
    char input[] = "(foo (bar) baz)";
    void* result = read(input);
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "(foo (bar) baz)"));

    printf("[0002] test_writer passed\n");
}

void test_0003_addition() {
    char input[] = "(+ 1 2)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "3") == 0);

    printf("[0003] test_addition passed\n");
}

void test_0004_subtraction() {
    char input[] = "(- 2 1)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "1") == 0);

    printf("[0004] test_subtraction passed\n");
}

void test_0005_multiplication() {
    char input[] = "(* 2 3)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "6") == 0);

    printf("[0005] test_multiplication passed\n");
}

void test_0006_division() {
    char input[] = "(/ 6 2)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "3") == 0);

    printf("[0006] test_division passed\n");
}

void test_0007_modulo() {
    char input[] = "(% 7 3)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "1") == 0);

    printf("[0007] test_modulo passed\n");
}

void test_0008_if_true() {
    char input[] = "(if #t 2 3)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "2") == 0);

    printf("[0008] test_if_true passed\n");
}

void test_0009_if_false() {
    char input[] = "(if #f 2 3)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "3") == 0);

    printf("[0009] test_if_false passed\n");
}

void test_0010_equal_true() {
    char input[] = "(= 1 1)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "#t") == 0);

    printf("[0010] test_equal_true passed\n");
}

void test_0011_equal_false() {
    char input[] = "(= 1 2)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "#f") == 0);

    printf("[0011] test_equal_false passed\n");
}

void test_0012_define() {
    char input[] = "(define x 1)";
    void* result = read(input);
    void* r = eval(result);
    assert(r == NULL);

    printf("[0012] test_define passed\n");
}

void test_0013_quote() {
    char input[] = "(quote 1)";
    void* result = read(input);
    void* r = eval(result);
    assert(strcmp(r, "1") == 0);

    printf("[0013] test_quote passed\n");
}

void test_0014_cons() {
    char buffer[256];
    void* result = eval(read("(cons 1 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "(1 . 2)"));

    printf("[0014] test_cons passed\n");
}

void test_0015_car() {
    char buffer[256];
    void* result = eval(read("(car (cons 1 2))"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "1"));

    printf("[0015] test_car passed\n");
}

void test_0016_cdr() {
    char buffer[256];
    void* result = eval(read("(cdr (cons 1 2))"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "2"));

    printf("[0016] test_cdr passed\n");
}

void test_0017_list() {
    char buffer[256];
    void* result = eval(read("(list 1 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "(1 2)"));

    printf("[0017] test_list passed\n");
}

void test_0018_lambda() {
    char buffer[256];
    void* result = eval(read("((lambda (x) x) 1)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "1"));

    printf("[0018] test_lambda passed\n");
}

void test_0019_apostrophe() {
    char buffer[256];
    void* result = eval(read("'(1 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "(1 2)"));

    printf("[0019] test_apostrophe passed\n");
}

void test_0020_define_set() {
    char buffer[256];
    eval(read("(define x 1)"));
    eval(read("(set! x 2)"));
    void* result = eval(read("x"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "2"));

    printf("[0020] test_define_set passed\n");
}

void test_0021_addition_float() {
    char buffer[256];
    void* result = eval(read("(+ 1.1 2.2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "3.3") == 0);

    printf("[0021] test_addition_float passed\n");
}

void test_0022_subtraction_float() {
    char buffer[256];
    void* result = eval(read("(- 1.1 2.2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "-1.10000") == 0);

    printf("[0022] test_subtraction_float passed\n");
}

void test_0023_multiplication_float() {
    char buffer[256];
    void* result = eval(read("(* 1.1 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "2.2") == 0);

    printf("[0023] test_multiplication_float passed\n");
}

void test_0024_division_float() {
    char buffer[256];
    void* result = eval(read("(/ 2.2 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "1.1") == 0);

    printf("[0024] test_division_float passed\n");
}

void test_0025_modulo_float() {
    char buffer[256];
    void* result = eval(read("(% 2.2 2)"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "") == 0);

    printf("[0025] test_modulo_float passed\n");
}

void test_0026_define_get() {
    char buffer[256];
    eval(read("(define x 1)"));
    eval(read("(get x)"));
    void* result = eval(read("x"));
    get_exp_string(result, buffer, sizeof(buffer));
    assert(streq(buffer, "1"));

    printf("[0026] test_define_get passed\n");
}

int main() {
    test_0000_lexer();
    test_0001_reader();
    test_0002_writer();
    test_0003_addition();
    test_0004_subtraction();
    test_0005_multiplication();
    test_0006_division();
    test_0007_modulo();
    test_0008_if_true();
    test_0009_if_false();
    test_0010_equal_true();
    test_0011_equal_false();
    test_0012_define();
    test_0013_quote();
    test_0014_cons();
    test_0015_car();
    test_0016_cdr();
    test_0017_list();
    test_0018_lambda();
    test_0019_apostrophe();
    test_0020_define_set();
    test_0021_addition_float();
    test_0022_subtraction_float();
    test_0023_multiplication_float();
    test_0024_division_float();
    test_0025_modulo_float();
    test_0026_define_get();
    return 0;
}
