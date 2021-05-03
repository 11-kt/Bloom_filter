#ifndef BLOOM_FILTER_HASH_H
#define BLOOM_FILTER_HASH_H

#include "../Bloom/bloom.h"

uint64_t *hash(const uint8_t *element, int k, bloom *b);

#endif