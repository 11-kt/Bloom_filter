#ifndef BLOOM_FILTER_BLOOMSTRUCT_H
#define BLOOM_FILTER_BLOOMSTRUCT_H

#include <stdint.h>

struct BloomStruct {
    int size;
    int numOfElements;
    int hashNum;
    uint64_t seed;
    int numOfAddedElem;
    int *bitField;
};

typedef struct BloomStruct bloom;

#endif
