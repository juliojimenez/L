#include <stdio.h>
#include <string.h>
#include "writer.h"

// Helper function to compare strings
int streq(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

// Custom print function to get string representation (for assertions)
void get_exp_string(void* exp, char* buffer, size_t size) {
    FILE* stream = fmemopen(buffer, size, "w");
    if (stream) {
        FILE* old_stdout = stdout;
        stdout = stream;
        print_exp(exp);
        fflush(stream);
        stdout = old_stdout;
        fclose(stream);
    }
}
