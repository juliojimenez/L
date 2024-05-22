#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

typedef struct {
    char sym[32];
    void* val;
} Entry;

extern Entry entry[32];
extern char symbol[2048];

void* cpysym(void* sym);
void put(void* sym, void* val);
void* get(void* sym);

#endif
