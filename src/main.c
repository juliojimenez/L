#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define VERSION "0.0.4"

// 128 tokens, each 32 characters long
char token[128][32];

int lexer(char* input) {
    int ii = 0; // input index
    int ti = 0; // token index

    // loop through the input string
    while (input[ii] != '\0') {
        switch (input[ii]) {
            // ignore whitespace and newlines
            case ' ':
            case '\n':
                ++ii;
                break;
            // turn left parenthesis into a token
            case '(':
                token[ti][0] = '(';
                token[ti][1] = '\0';
                ++ii;
                ++ti;
                break;
            // turn right parenthesis into a token
            case ')':
                token[ti][0] = ')';
                token[ti][1] = '\0';
                ++ii;
                ++ti;
                break;
            // everything else is a symbol
            default:
                for (int i = 0; ; ++i) {
                    if (input[ii] != ' ' &&
                        input[ii] != '(' &&
                        input[ii] != ')' &&
                        input[ii] != '\n' &&
                        input[ii] != '\0') {
                        token[ti][i] = input[ii++];
                        break;
                    } else {
                        token[ti][i] = '\0';
                        break;
                    }
                }
                ++ti;
                break;
        }
    }
    return ti;
}

int curtok;

char* nexttok() {
    return token[curtok++];
}

char* peektok() {
    return token[curtok];
}

typedef struct {
    void* car;
    void* cdr;
} Pair;

Pair text[256];
Pair* textptr;

Pair* cons(void* x, void* y) {
    textptr->car = x;
    textptr->cdr = y;
    return textptr++;
}

int ispair(void* x) {
    return x >= (void*)&text && x < (void*)&text[256];
}

int main(int argc, char** argv) {
    printf("L v%s\n", VERSION);
}
