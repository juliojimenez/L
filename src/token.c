#include "lexer.h"

int curtok;

char* nexttok() {
    return token[curtok++];
}

char* peektok() {
    return token[curtok];
}
