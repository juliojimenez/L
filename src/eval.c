char* ret[32];

void* eval_exp(void* exp) {
    if (istext(exp)) {
        Text* text = exp;
        if (strcmp("+", text->car) == 0) {
            void* left = eval_exp(text->cdr->car);
            void* right = eval_exp(text->cdr->cdr->car);
            sprintf(ret, "%d", atoi(left) + atoi(right));
            return ret;
        }
    }
    return exp;
}

void* eval(void* exp) {
  return exp;
}
