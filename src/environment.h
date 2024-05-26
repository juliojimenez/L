#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "liststruct.h"

extern char symbol[2048];

extern Pair list[1280];

int islist(const void* x);
Pair* cons(void* x, void* y);
void* cpysym(void* sym);
void* lambda(Text* args, Text* body, void* env);

typedef struct {
    char sym[32];
    void* val;
} Entry;

typedef struct Env {
    Entry entry[32];
    Entry* entryptr;
    struct Env* next;
} Env;

extern Env global;

Env* extend(Env* env);

extern Entry entry[32];






int isenv(void* x);
void put(void* sym, void* val, Env* env);
void* get(void* sym, Env* env);

#endif
