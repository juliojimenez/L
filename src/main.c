#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "lexer.h"
#include "token.h"
#include "liststruct.h"

#define VERSION "0.0.5"

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

int main(int argc, char** argv) {
    printf("L v%s\n", VERSION);
}
