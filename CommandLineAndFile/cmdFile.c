#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "cmdFile.h"
#include "../Errors/errors.h"
#include <windows.h>

bloom *readFile() {
    FILE *file = fopen("C:\\Users\\GamerPro\\CLionProjects\\Bloom-filter\\input.txt", "r");
    if (file == NULL) errors(1);
    char ch;
    bloom *b;
    char *string = (char *)calloc(1, sizeof(char));
    int line = 0;
    int count = 0;
    int index = 0;
    int filterLength = 0;
    int numOfElem = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
            index = 0;
            count = 0;
        }
        if (count > 14 && line == 0) {
            string[index] = ch;
            index++;
            string = (char *)realloc(string, index + 1);
        }
        if (count > 19 && line == 1) {
            string[index] = ch;
            index++;
            string = (char *)realloc(string, index + 1);
        }
        if (count > 9 && line == 2 && ch != ' ') {
            string[index] = ch;
            index++;
            if (index > 1) errors(5);
            string = (char *)realloc(string, index + 1);
        }
        if (line == 1 && filterLength == 0) {
            filterLength = strtol(string, 0, 10);
            string = (char *)calloc(1, sizeof(char));
        }
        if (line == 2 && numOfElem == 0) {
            numOfElem = strtol(string, 0, 10);
            string = (char *)calloc(1, sizeof(char));
            if (filterLength < 1 || numOfElem < 1) errors(3);
            b = create(filterLength, numOfElem);
            if (b->hashNum < 1) errors(4);
        }
        if (ch == ' ' && line == 2 && count > 10) {
            index = 0;
            add(string, b);
            string = (char *)calloc(1, sizeof(char));
        }
        count++;
    }
    if (line > 2) errors(2);
    add(string, b);
    free(string);
    fclose(file);
    return b;
}

int commandLine(char *line, bloom *b) {
    SetConsoleOutputCP(CP_UTF8);
    scanf("%s", line);
    if (strlen(line) < 2) errors(6);
    if (line[0] == '-' && line[1] == 'e') return 0;
    if (line[0] == '-' && line[1] == 'h') {
        printf("Командная строка имеет вид -key_n\n");
        printf("-key - режим работы\n-a - добавление элемента\n-c - проверка содержания\n-h - помощь\n-e - выход");
        printf("\n_n - элемент, который необходимо добавить или проверить");
    }
    if (line[0] == '-' && line[1] == 'a') {
        if (strlen(line) == 4) {
            if (b->numOfAddedElem + 1 <= b->numOfElements) {
                add(&line[3], b);
                printf("Элемент: %c успешно добавлен", line[3]);
            } else errors(7);
        } else errors(8);
    }
    if (line[0] == '-' && line[1] == 'c') {
        if (strlen(line) == 4) {
            if (contains(&line[3], b) == 1) printf("Элемент: %c возможно есть", line[3]);
            else printf("Элемента: %c точно нет", line[3]);
        } else errors(8);
    }
    return 1;
}
