#include <ctype.h>
#include <stdbool.h>

bool isdigit_or_dot(char c) {
  return isdigit(c) || c == '.';
}

// 128 tokens, each 32 characters long
char token[128][32];

int lexer(char* input) {
    int ii = 0; // input index
    int ti = 0; // token index

    // loop through the input string
    while (input[ii] != '\0') {
        switch (input[ii]) {
            // ignore whitespace and newlines
            case ' ':
            case '\n':
                ++ii;
                break;
            // turn left parenthesis into a token
            case '(':
                token[ti][0] = '(';
                token[ti][1] = '\0';
                ++ii;
                ++ti;
                break;
            // turn right parenthesis into a token
            case ')':
                token[ti][0] = ')';
                token[ti][1] = '\0';
                ++ii;
                ++ti;
                break;
            // turn an apostrophe into a token
            case '\'':
                token[ti][0] = '\'';
                token[ti][1] = '\0';
                ++ii;
                ++ti;
                break;
            // everything else is a symbol
            default:
                for (int i = 0;; ++i) {
                    if (input[ii] != ' ' &&
                        input[ii] != '(' &&
                        input[ii] != ')' &&
                        input[ii] != '\n' &&
                        input[ii] != '\0') {
                        token[ti][i] = input[ii++];
                    } else if (isdigit_or_dot(input[ii]) || isalpha(input[ii])) {
                        token[ti][i] = input[ii++];
                    } else {
                        token[ti][i] = '\0';
                        break;
                    }
                }
                ++ti;
                break;
        }
    }
    return ti;
}
