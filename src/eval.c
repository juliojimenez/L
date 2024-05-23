#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liststruct.h"
#include "environment.h"

char ret[32];

void* eval_exp(void* exp);

void* evalargs(Text* args) {
    return cons(eval_exp(args->car), args->cdr ? evalargs(args->cdr) : NULL);
}

void* eval_exp(void* exp) {
    if (istext(exp)) {
        Text* text = exp;
        if (strcmp("list", text->car) == 0) {
            return evalargs(text->cdr);
        } else if (strcmp("cons", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            return cons(left, right);
        } else if (strcmp("car", text->car) == 0) {
            Pair* pair = eval_exp(text->cdr->car);
            return pair->car;
        } else if (strcmp("cdr", text->car) == 0) {
            Pair* pair = eval_exp(text->cdr->car);
            return pair->cdr;
        } else if (strcmp("define", text->car) == 0) {
            void* var = text->cdr->car;
            void* val = eval_exp(text->cdr->cdr->car);
            put(var, val);
            return "done";
        } else if (strcmp("quote", text->car) == 0) {
            return text->cdr->car;
        } else if (strcmp("=", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            if (left && right) {
                return strcmp(left, right) == 0 ? "#t" : "#f";
            } else {
                return left == right ? "#t" : "#f";
            }
        } else if (strcmp("if", text->car) == 0) {
            void* conditional = eval_exp(text->car);
            if (strcmp("#t", text->cdr->car) == 0) {
                return eval_exp(text->cdr->cdr->car);
            } else {
                return eval_exp(text->cdr->cdr->cdr->car);
            }
        } else if (strcmp("+", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) + atoi(right));
            return ret;
        } else if (strcmp("-", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) - atoi(right));
            return ret;
        } else if (strcmp("*", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) * atoi(right));
            return ret;
        } else if (strcmp("/", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) / atoi(right));
            return ret;
        } else if (strcmp("%", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) % atoi(right));
            return ret;
        }
    }
    return isdigit(*((char*)exp)) ||
           strcmp(exp, "#t") == 0 ||
           strcmp(exp, "#f") == 0 ? exp : get(exp);
}

void* eval(void* exp) {
  return eval_exp(exp);
}
