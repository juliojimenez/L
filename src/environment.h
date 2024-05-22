#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "liststruct.h"

typedef struct {
    char sym[32];
    void* val;
} Entry;

extern Entry entry[32];
extern char symbol[2048];

extern Pair list[1280];

int islist(void* x);
Pair* cons(void* x, void* y);

void* cpysym(void* sym);
void put(void* sym, void* val);
void* get(void* sym);

#endif
