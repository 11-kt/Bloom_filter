#ifndef BLOOM_FILTER_CMDFILE_H
#define BLOOM_FILTER_CMDFILE_H

#include "../Bloom/bloom.h"

bloom *readFile(FILE *file);
int commandLine(char *line, bloom *b);

#endif
