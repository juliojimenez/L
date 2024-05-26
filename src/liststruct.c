#include <assert.h>

typedef struct Pair {
    void* car;
    void* cdr;
} Pair;

typedef struct Text {
    char* car;
    struct Text* cdr;
} Text;

Pair text[256];
Pair* textptr;

int istext(void* x) {
    return x >= (void*)&text && x < (void*)&text[256];
}

Pair* tcons(void* x, void* y) {
    assert(istext(textptr));
    textptr->car = x;
    textptr->cdr = y;
    return textptr++;
}
