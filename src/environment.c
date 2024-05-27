#include <assert.h>
#include <string.h>
#include "liststruct.h"

char symbol[2048];
char* symbolptr = symbol;

Pair list[1280];
Pair* listptr = list;

int islist(const void* x) {
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

void* cpy(Text* txt) {
    if (istext(txt) || islist(txt)) {
        if (istext(txt->car) || islist(txt->car)) {
            return cons(cpy((Text*)txt->car), text->cdr ? cpy(txt->cdr) : NULL);
        } else {
            return cons(cpysym(txt->car), text->cdr ? cpy(txt->cdr) : NULL);
        }
    }
    return cpysym(txt);
}

void* cpylambda(Pair* val) {
    Pair* lambda = val->cdr;
    lambda->car = lambda->car ? cpy(lambda->car) : NULL;
    lambda->cdr = cpy(lambda->cdr);
    return val;
}

void* lambda(Text* args, Text* body, void* env) {
    return cons(env, cons(args, body));
}

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

int isenv(const void* x);

Env* extend(Env* env) {
    assert(isenv(frameptr));
    frameptr->next = env;
    frameptr->entryptr = frameptr->entry;
    return frameptr++;
}

void retract() {
  assert(isenv(frameptr));
  frameptr--;
  memset(frameptr->entry, 0, sizeof(Entry[32]));
}

int isenv(const void* x) {
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

void set(void* sym, void* val, Env* env) {
    assert(env);
    Entry* seek = env->entryptr;
    for (; seek != env->entry - 1; --seek) {
        if (strcmp(seek->sym, sym) == 0) {
            if (val < (void*)100) {
                seek->val = val;
            } else if (istext(val) || islist(val)) {
                Pair* pair = val;
                if (isenv(pair->car)) {
                    seek->val = cpylambda(val);
                } else {
                    seek->val = cpy(val);
                }
            } else {
                seek->val = cpysym(val);
            }
            return;
        }
    }
    return set(sym, val, env->next);
}
