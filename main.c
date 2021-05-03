#include <stdio.h>
#include <malloc.h>
#include "Bloom/bloom.h"
#include "Errors/errors.h"
#include "CommandLineAndFile/cmdFile.h"

int main() {
    FILE *file = fopen("C:\\Users\\GamerPro\\CLionProjects\\Bloom-filter\\input.txt", "r");
    if (file == NULL) errors(1);
    bloom *b = readFile(file);
    fclose(file);

    char *cmdLine = (char *)malloc(4);
    int cmd = 1;
    while (cmd == 1) {
     cmd = commandLine(cmdLine, b);
     cmdLine = (char *)malloc(4);
    }
    free(cmdLine);
    delete(b);

    return 0;
}