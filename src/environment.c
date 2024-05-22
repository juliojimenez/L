#include <assert.h>
#include <string.h>
#include "liststruct.h"

typedef struct {
    char sym[32];
    void* val;
} Entry;

Entry entry[32];
Entry* entryptr = entry;

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

void put(void* sym, void* val) {
    strcpy(entryptr->sym, sym);
    if (istext(val) || islist(val)) {
        entryptr->val = cpy(val);
    } else {
        entryptr->val = cpysym(val);
    }
    entryptr++;
}

void* get(void* sym) {
    Entry* seek = entryptr;
    for (; seek != entry - 1; --seek) {
        if (strcmp(seek->sym, sym) == 0) {
            return seek->val;
        }
    }
    return NULL;
}
