#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liststruct.h"
#include "environment.h"

char ret[32];

void* eval_exp(void* exp, Env* env);
void* apply(void* func, Text* args, Env* env);

void* evalargs(Text* args, Env* env) {
    return cons(eval_exp(args->car, env), args->cdr ? evalargs(args->cdr, env) : NULL);
}

void* eval_exp(void* exp, Env* env) {
    if (istext(exp) || islist(exp)) {
        Text* text = exp;
        if (strcmp("define", text->car) == 0) {
            void* var = text->cdr->car;
            void* val = eval_exp(text->cdr->cdr->car, env);
            put(var, val, env);
            return NULL;
        } else if (strcmp("quote", text->car) == 0) {
            return text->cdr->car;
        } else if (strcmp("if", text->car) == 0) {
            void* conditional = eval_exp(text->cdr->car, env);
            if (strcmp(conditional, "#t") == 0) {
                return eval_exp(text->cdr->cdr->car, env);
            } else {
                return eval_exp(text->cdr->cdr->cdr->car, env);
            }
        } else {
            void* fun = eval_exp(text->car, env);
            return apply(fun, text->cdr, env);
        }
    }
    return isdigit(*((char*)exp)) ||
           strcmp(exp, "#t") == 0 ||
           strcmp(exp, "#f") == 0 ? exp : get(exp, env);
}

void* eval(void* exp) {
  return eval_exp(exp, &global);
}

void* apply(void* func, Text* args, Env* env) {
    char evret[32];
    if (func == (void*)1) {
        int left = atoi(eval_exp(args->car, env));
        int right = atoi(eval_exp(args->cdr->car, env));
        sprintf(evret, "%d", left + right);
        return cpysym(evret);
    } else if (func == (void*)2) {
        int left = atoi(eval_exp(args->car, env));
        int right = atoi(eval_exp(args->cdr->car, env));
        sprintf(evret, "%d", left - right);
        return cpysym(evret);
    } else if (func == (void*)3) {
        int left = atoi(eval_exp(args->car, env));
        int right = atoi(eval_exp(args->cdr->car, env));
        sprintf(evret, "%d", left * right);
        return cpysym(evret);
    } else if (func == (void*)4) {
        int left = atoi(eval_exp(args->car, env));
        int right = atoi(eval_exp(args->cdr->car, env));
        sprintf(evret, "%d", left / right);
        return cpysym(evret);
    } else if (func == (void*)5) {
        Pair* pair = eval_exp(args->car, env);
        return pair->car;
    } else if (func == (void*)6) {
        Pair* pair = eval_exp(args->car, env);
        return pair->cdr;
    } else if (func == (void*)7) {
        char* left = eval_exp(args->car, env);
        char* right = eval_exp(args->cdr->car, env);
        if (left && right) {
            return strcmp(left, right) == 0 ? "#t" : "#f";
        } else {
            return left == right ? "#t" : "#f";
        }
    } else if (func == (void*)8) {
        void* left = eval_exp(args->car, env);
        void* right = eval_exp(args->cdr->car, env);
        return cons(left, right);
    } else if (func == (void*)9) {
        return evalargs(args, env);
    } else if (func == (void*)10) {
        int left = atoi(eval_exp(args->car, env));
        int right = atoi(eval_exp(args->cdr->car, env));
        sprintf(evret, "%d", left % right);
        return cpysym(evret);
    }
    assert(0);
}
