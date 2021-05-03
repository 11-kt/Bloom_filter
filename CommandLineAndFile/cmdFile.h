#ifndef BLOOM_FILTER_CMDFILE_H
#define BLOOM_FILTER_CMDFILE_H

#include "../Bloom/bloom.h"

bloom *readFile();
int commandLine(char *line, bloom *b);

#endif
