#include <malloc.h>
#include "hash.h"

uint64_t *hash(const uint8_t *element, int k, bloom *b) {
    uint64_t *hash = (uint64_t*)calloc(k, sizeof(uint64_t));
    uint64_t result = 1;
    int index = 0;
    const int halfElem = *element / 2;
    int halfK = k / 2;
    int start = 1;
    for (int i = 0; i < *element; ++i) {
        result = ((result * b->seed + i) * k) & 0xFFFFFFFF;
        if (i == halfElem) {
            for (int j = start; j < halfK; ++j) {
                hash[index] = result * j + j;
                index++;
            }
            start = halfK;
            result = 1;
        }
        if (i == *element - 1) {
            for (int j = start; j < k + 1; ++j) {
                hash[index] = (result + j) * j;
                index++;
            }
        }
    }
    return hash;
}
