#ifndef EVAL_H
#define EVAL_H

#include "environment.h"

void* evalargs(Text* args, Env* env);
void* eval_exp(void* exp, Env* env);
void* eval(void* exp);

#endif
