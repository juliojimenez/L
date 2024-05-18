typedef struct {
    void* car;
    void* cdr;
} Pair;

typedef struct Text {
    char* car;
    struct Text* cdr;
} Text;

Pair text[256];
Pair* textptr;

Pair* tcons(void* x, void* y) {
    textptr->car = x;
    textptr->cdr = y;
    return textptr++;
}

int istext(void* x) {
    return x >= (void*)&text && x < (void*)&text[256];
}
