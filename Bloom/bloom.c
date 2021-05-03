#include <malloc.h>
#include <stdlib.h>
#include "bloom.h"
#include "math.h"
#include "../Hash/hash.h"

void add(const void *element, bloom *b) {
    uint64_t *hashed = hash((const uint8_t*)element, b->hashNum, b);
    for (int i = 0; i < b->hashNum; ++i) b->bitField[hashed[i] % b->size] = 1;
    b->numOfAddedElem++;
    free(hashed);
}

int contains(const void *element, bloom *b) {
    uint64_t *hashed = hash((const uint8_t*)element, b->hashNum, b);
    for (int i = 0; i < b->hashNum; ++i) {
        if (b->bitField[hashed[i] % b->size] != 1) {
            free(hashed);
            return 0;
        }
    }
    free(hashed);
    return 1;
}

bloom *create(int length, int elementsNum) {
    bloom *b = (bloom *)calloc(1, sizeof(bloom));
    b->size = length;
    b->numOfElements = elementsNum;
    b->hashNum = (int)(log(2) * length / elementsNum);
    b->seed = rand() * 32 + 32;
    b->numOfAddedElem = 0;
    b->bitField = (int *)calloc(length, sizeof(int));
    return b;
}

void delete(bloom *b) {
    if (b->bitField != NULL) free(b->bitField);
    free(b);
}