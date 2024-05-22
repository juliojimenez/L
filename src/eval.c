#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liststruct.h"

char ret[32];

void* eval_exp(void* exp) {
    if (istext(exp)) {
        Text* text = exp;
        if (strcmp("=", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            return strcmp(left, right) == 0 ? "#t" : "#f";
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
    return exp;
}

void* eval(void* exp) {
  return eval_exp(exp);
}
