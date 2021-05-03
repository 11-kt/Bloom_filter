#include <stdio.h>
#include "test.h"
#include "../Bloom/bloom.h"

void test1() {
    printf("Test: 1\n");
    int length = 6;
    int elementsNum = 2;
    bloom *b = create(length, elementsNum);

    int elem1 = 6;
    add(&elem1, b);
    int cont = contains(&elem1, b);
    printf("expected: true | result: ");
    if (cont == 1) printf("true");
    else printf("false");
    printf("\n");

    int elem2 = 'c';
    add(&elem2, b);
    cont = contains(&elem2, b);
    printf("expected: true | result: ");
    if (cont == 1) printf("true");
    else printf("false");

    delete(b);
}

void test2() {
    printf("\n\nTest: 2\n");
    int length = 12;
    int elementsNum = 4;
    bloom *b = create(length, elementsNum);

    int elem = 1;
    add(&elem, b);
    elem++;
    add(&elem, b);
    int elem1 = 'c';
    add(&elem1, b);
    int cont = contains(&elem1, b);
    printf("expected: true | result: ");
    if (cont == 1) printf("true\n");
    else printf("false\n");

    double elem2 = 1.01;
    cont = contains(&elem2, b);
    printf("expected: false | result: ");
    if (cont == 1) printf("true\n");
    else printf("false\n");

    add(&elem2, b);
    cont = contains(&elem1, b);
    printf("expected: true | result: ");
    if (cont == 1) printf("true\n");
    else printf("false\n");

    delete(b);
}

void test3() {
    printf("\n\nTest: 3\n");
    int length = 3;
    int elementsNum = 1;
    bloom *b = create(length, elementsNum);

    char *elem = "asd";
    int cont = contains(&elem, b);
    printf("expected: false | result: ");
    if (cont == 1) printf("true\n");
    else printf("false\n");

    add(&elem, b);
    cont = contains(&elem, b);
    printf("expected: true | result: ");
    if (cont == 1) printf("true\n");
    else printf("false\n");

    delete(b);
}

//int main() {
//    test1();
//    test2();
//    test3();
//    return 0;
//}