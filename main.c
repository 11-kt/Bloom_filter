#include <malloc.h>
#include "Bloom/bloom.h"
#include "CommandLineAndFile/cmdFile.h"

int main() {
    bloom *b = readFile();
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