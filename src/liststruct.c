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
