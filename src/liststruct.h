#ifndef LISTSTRUCT_H
#define LISTSTRUCT_H

typedef struct {
    void* car;
    void* cdr;
} Pair;

typedef struct Text {
    char* car;
    struct Text* cdr;
} Text;

extern Pair text[256];
extern Pair* textptr;

Pair* tcons(void* x, void* y);
int ispair(void* x);

#endif
