#ifndef BLOOM_FILTER_BLOOM_H
#define BLOOM_FILTER_BLOOM_H

#include "bloomStruct.h"

void add(const void *element, bloom *b);
int contains(const void *element, bloom * b);
bloom *create(int length, int elementsNum);
void delete(bloom *b);

#endif