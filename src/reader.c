#include <stdio.h>
#include "lexer.h"
#include "liststruct.h"
#include "token.h"

void* read_exp();

void* read_list() {
    char* tok = peektok();
    if (tok[0] == ')') {
        nexttok();
        return NULL;
    } else {
        void* fst = read_exp();
        void* snd = read_list();
        return cons(fst, snd);
    }
}

void* read_exp() {
    char* tok = nexttok();
    if (tok[0] == '(') {
        return read_list();
    } else {
        return tok;
    }
}

void* read(char* ln) {
    // initialize the lexer and list memory
    curtok = 0;
    textptr = text;

    lexer(ln);
    return read_exp();
}
