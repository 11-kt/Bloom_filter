#include <malloc.h>
#include "Bloom/bloom.h"
#include "CommandLineAndFile/cmdFile.h"
#include "Errors/errors.h"

int main(int argc, char *args[]) {
    if (argc != 2) errors(1, args[1]);
    bloom *b = readFile(args[1]);
    char *cmdLine = (char *)malloc(4);
    if (cmdLine == NULL) errors(11, "cmdLine");
    int cmd = 1;
    while (cmd == 1) {
     cmd = commandLine(cmdLine, b, args[1]);
     cmdLine = (char *)malloc(4);
     if (cmdLine == NULL) errors(11, "cmdLine");
    }
    free(cmdLine);
    delete(b);
    return 0;
}