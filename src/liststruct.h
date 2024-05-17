#ifndef LISTSTRUCT_H
#define LISTSTRUCT_H

typedef struct {
    void* car;
    void* cdr;
} Pair;

extern Pair text[256];
extern Pair* textptr;

Pair* cons(void* x, void* y);
int ispair(void* x);

#endif
