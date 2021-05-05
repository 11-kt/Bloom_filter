#include <malloc.h>
#include "hash.h"
#include "../Errors/errors.h"

uint64_t *hash(const uint8_t *element, int k, bloom *b) {
    // k - количество хэш функций (из формулы: k = ln2 * n/m (где n – длина поля, m – кол-во элементов))
    uint64_t *hash = (uint64_t*)calloc(k, sizeof(uint64_t));
    if (hash == NULL) errors(11, "hash");
    uint64_t result = 1;
    int index = 0;
    const int halfElem = *element / 2;
    int halfK = k / 2;
    int start = 1;
    for (int i = 0; i < *element; ++i) {
        // Создание начального значения хэша и приведение его к 64битному числу
        result = ((result * b->seed + i) * k) & 0xFFFFFFFF;
        // для первой половины element последующий расчет различных k / 2 хэшей идет следующим образом:
        if (i == halfElem) {
            for (int j = start; j < halfK; ++j) {
                hash[index] = result * j + j;
                index++;
            }
            start = halfK;
            result = 1;
        }
        // для второй половины последующий расчет различных [k / 2; k] хэшей идет следующим образом:
        // такой подход сделан для возможности создания разнообразных k хэшей для каждого элемента
        if (i == *element - 1) {
            for (int j = start; j < k + 1; ++j) {
                hash[index] = (result + j) * j;
                index++;
            }
        }
    }
    return hash;
}