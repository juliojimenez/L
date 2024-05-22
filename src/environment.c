#include <string.h>

typedef struct {
    char sym[32];
    void* val;
} Entry;

Entry entry[32];
Entry* entryptr = entry;

char symbol[2048];
char* symbolptr = symbol;

void* cpysym(void* sym) {
    if (sym) {
        sym = strcpy(symbolptr, sym);
        symbolptr = symbolptr + strlen(sym) + 1;
    }
    return sym;
}

void put(void* sym, void* val) {
    strcpy(entryptr->sym, sym);
    entryptr->val = cpysym(val);
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
