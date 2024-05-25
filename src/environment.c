#include <assert.h>
#include <string.h>
#include "liststruct.h"

typedef struct {
    char sym[32];
    void* val;
} Entry;

typedef struct Env {
    Entry entry[32];
    Entry* entryptr;
    struct Env* next;
} Env;

Env global = {
    {{ .sym = "+", .val = (void*)1 },
     { .sym = "-", .val = (void*)2 },
     { .sym = "*", .val = (void*)3 },
     { .sym = "/", .val = (void*)4 },
     { .sym = "car", .val = (void*)5 },
     { .sym = "cdr", .val = (void*)6 },
     { .sym = "=", .val = (void*)7 },
     { .sym = "cons", .val = (void*)8 },
     { .sym = "list", .val = (void*)9 },
     { .sym = "%", .val = (void*)10}},
    .entryptr = global.entry + 10,
    NULL
};

Env frame[128];
Env* frameptr = frame;

int isenv(void* x);

Env* extend(Env* env) {
    frameptr->next = env;
    frameptr->entryptr = frameptr->entry;
    return frameptr++;
}

void retract() {
  assert(isenv(frameptr));
  frameptr--;
  memset(frameptr->entry, 0, sizeof(Entry[32]));
}

char symbol[2048];
char* symbolptr = symbol;

Pair list[1280];
Pair* listptr = list;

int islist(void* x) {
    return x >= (void*)&list && x < (void*)&list[1280];
}

Pair* cons(void* x, void* y) {
    assert(islist(listptr));
    listptr->car = x;
    listptr->cdr = y;
    return listptr++;
}

void* cpysym(void* sym) {
    if (sym) {
        sym = strcpy(symbolptr, sym);
        symbolptr = symbolptr + strlen(sym) + 1;
    }
    return sym;
}

void* cpy(Text* text) {
    if (istext(text) || islist(text)) {
        if (istext(text->car) || islist(text->car)) {
            return cons(cpy((Text*)text->car), text->cdr ? cpy(text->cdr) : NULL);
        } else {
            return cons(cpysym(text->car), text->cdr ? cpy(text->cdr) : NULL);
        }
    }
    return cpysym(text);
}

void* cpylambda(Pair* val) {
    Pair* lambda = val->cdr;
    lambda->car = lambda->car ? cpy(lambda->car) : NULL;
    lambda->cdr = cpy(lambda->cdr);
    return val;
}

int isenv(void* x) {
    return x >= (void*)&frame && x < (void*)&frame[128] || x == (void*)&global;
}

void put(void* sym, void* val, Env* env) {
    assert(env);
    assert(env->entryptr >= (Entry*)&env->entry && env->entryptr < (Entry*)&env->entry[32]);
    strcpy(env->entryptr->sym, sym);
    if (val < (void*)100) {
        env->entryptr->val = val;
        env->entryptr++;
        return;
    }
    if (istext(val) || islist(val)) {
        Pair* pair = val;
        if (isenv(pair->car)) {
            env->entryptr->val = cpylambda(val);
        } else {
            env->entryptr->val = cpy(val);
        }
    } else {
        env->entryptr->val = cpysym(val);
    }
    env->entryptr++;
}

void* get(void* sym, Env* env) {
    assert(env);
    Entry* seek = env->entryptr;
    for (; seek != env->entry - 1; --seek) {
        if (strcmp(seek->sym, sym) == 0) {
            return seek->val;
        }
    }
    return get(sym, env->next);
}
