#ifndef BLOOM_FILTER_CMDFILE_H
#define BLOOM_FILTER_CMDFILE_H

#include "../Bloom/bloom.h"

bloom *readFile(char *fileName);
int commandLine(char *line, bloom *b, char *fileName);

#endif