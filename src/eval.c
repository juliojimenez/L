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

void* lambda(Text* args, Text* body, void* env) {
    return cons(env, cons(args, body));
}

void* eval_exp(void* exp, Env* env) {
    if (istext(exp) || islist(exp)) {
        Text* txt = exp;
        if (strcmp("define", txt->car) == 0) {
            void* var = txt->cdr->car;
            void* val = eval_exp(txt->cdr->cdr->car, env);
            put(var, val, env);
            return NULL;
        } else if (strcmp("quote", txt->car) == 0) {
            return txt->cdr->car;
        } else if (strcmp("if", txt->car) == 0) {
            void* conditional = eval_exp(txt->cdr->car, env);
            if (strcmp(conditional, "#t") == 0) {
                return eval_exp(txt->cdr->cdr->car, env);
            } else {
                return eval_exp(txt->cdr->cdr->cdr->car, env);
            }
        } else if (strcmp("lambda", txt->car) == 0) {
            return lambda((Text*)txt->cdr->car, txt->cdr->cdr, env);
        } else {
            void* fun = eval_exp(txt->car, env);
            return apply(fun, txt->cdr, env);
        }
    }
    return isdigit(*((char*)exp)) ||
           strcmp(exp, "#t") == 0 ||
           strcmp(exp, "#f") == 0 ? exp : get(exp, env);
}

void* eval(void* exp) {
  return eval_exp(exp, &global);
}

void* evalbody(Text* body, Env* env) {
    void* val = eval_exp(body->car, env);
    if (body->cdr) {
        return evalbody(body->cdr, env);
    } else {
        return val;
    }
}

void parameterize(Text* args, Text* para, Env* env) {
    put(para->car, args->car, env);
    if (args->cdr != NULL) {
        parameterize(args->cdr, para->cdr, env);
    }
}

void* apply(void* func, Text* args, Env* env) {
    if (islist(func)) {
        Pair* pair = func;
        Env* closure = pair->car;
        Pair* lambda = pair->cdr;
        Text* para = lambda->car;
        Text* body = lambda->cdr;
        Env* lambdaenv = extend(closure);
        if (para) {
            Text* evargs = evalargs(args, env);
            parameterize(evargs, para, lambdaenv);
        }
        return evalbody(body, lambdaenv);
    } else {
        char evret[32];
        if (func == (void*)1) {
            int left = atoi(eval_exp(args->car, env));
            int right = atoi(eval_exp(args->cdr->car, env));
            snprintf(evret, sizeof(int), "%d", left + right);
            return cpysym(evret);
        } else if (func == (void*)2) {
            int left = atoi(eval_exp(args->car, env));
            int right = atoi(eval_exp(args->cdr->car, env));
            snprintf(evret, sizeof(int), "%d", left - right);
            return cpysym(evret);
        } else if (func == (void*)3) {
            int left = atoi(eval_exp(args->car, env));
            int right = atoi(eval_exp(args->cdr->car, env));
            snprintf(evret, sizeof(int), "%d", left * right);
            return cpysym(evret);
        } else if (func == (void*)4) {
            int left = atoi(eval_exp(args->car, env));
            int right = atoi(eval_exp(args->cdr->car, env));
            snprintf(evret, sizeof(int), "%d", left / right);
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
            snprintf(evret, sizeof(int), "%d", left % right);
            return cpysym(evret);
        }
    }
    assert(0);
}
