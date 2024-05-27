#include <stdio.h>
#include "eval.h"
#include "reader.h"
#include "writer.h"

#define VERSION "0.0.17"

int main(int argc, char** argv) {
    printf("L v%s\n\n", VERSION);
    printf("> ");

    char buffer[256];
    while (fgets(buffer, 256, stdin)) {
        print(eval(read(buffer)));
        printf("> ");
    }
    return 0;
}
