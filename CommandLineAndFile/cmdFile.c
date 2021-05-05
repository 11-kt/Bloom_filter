#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "cmdFile.h"
#include "../Errors/errors.h"
#include <windows.h>

void controlSection(int line, int count, char *currentSection) {
    char *section;
    if (line == 0) {
        section = "Filter length: ";
        for (int i = 0; i < count; ++i) {
            if (currentSection[i] != section[i]) errors(4, currentSection);
        }
    }
    if (line == 1) {
        section = "Number of elements: ";
        for (int i = 0; i < count; ++i) {
            if (currentSection[i] != section[i]) errors(4, currentSection);
        }
    }
    if (line == 2) {
        section = "Elements: ";
        for (int i = 0; i < count; ++i) {
            if (currentSection[i] != section[i]) errors(4, currentSection);
        }
    }
}

bloom *readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) errors(2, fileName);
    char ch;
    bloom *b;
    char *string = (char *)calloc(1, sizeof(char));
    if (string == NULL) errors(11, "string");
    char *controlOfSections = (char *)calloc(1, sizeof(char));
    if (controlOfSections == NULL) errors(11, "controlOfSections");
    // Текущая строка line
    int line = 0;
    // Переменная count используется для проверки текущего символа (текущей строки line)
    int count = 0;
    int index = 0;
    int filterLength = 0;
    int numOfElem = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
            index = 0;
            count = 0;
            controlOfSections = (char *)calloc(1, sizeof(char));
            if (controlOfSections == NULL) errors(11, "controlOfSections");
        }
        // Проверка, является ли текущий символ строки 1 - 16м
        if (count == 15 && line == 0) controlSection(line, count, controlOfSections);
        if (count > 14 && line == 0) {
            string[index] = ch;
            index++;
            string = (char *)realloc(string, index + 1);
            if (string == NULL) errors(12, "string");
        }
        // Проверка, является ли текущий символ строки 2 - 20м
        if (count == 20 && line == 1) controlSection(line, count, controlOfSections);
        if (count > 19 && line == 1) {
            string[index] = ch;
            index++;
            string = (char *)realloc(string, index + 1);
            if (string == NULL) errors(12, "string");
        }
        // Проверка, является ли текущий символ строки 3 - 10м
        if (count == 10 && line == 2) controlSection(line, count, controlOfSections);
        if (count > 9 && line == 2 && ch != ' ') {
            string[index] = ch;
            index++;
            if (index > 1) errors(7, fileName);
            string = (char *)realloc(string, index + 1);
            if (string == NULL) errors(12, "string");
        }
        if (line == 1 && filterLength == 0) {
            filterLength = strtol(string, 0, 10);
            string = (char *)calloc(1, sizeof(char));
            if (string == NULL) errors(11, "string");
        }
        if (line == 2 && numOfElem == 0) {
            numOfElem = strtol(string, 0, 10);
            string = (char *)calloc(1, sizeof(char));
            if (string == NULL) errors(11, "string");
            if (filterLength < 1 || numOfElem < 1) errors(5, fileName);
            b = create(filterLength, numOfElem);
            if (b->hashNum < 1) errors(6, fileName);
        }
        if (ch == ' ' && line == 2 && count > 10) {
            index = 0;
            add(string, b);
            string = (char *)calloc(1, sizeof(char));
            if (string == NULL) errors(11, "string");
        }
        if (ch != '\n') {
            controlOfSections[count] = ch;
            count++;
            controlOfSections = (char *) realloc(controlOfSections, count + 1);
            if (controlOfSections == NULL) errors(12, "controlOfSections");
        }
    }
    if (line > 2) errors(3, fileName);
    add(string, b);
    free(string);
    free(controlOfSections);
    fclose(file);
    printf("Конфигурационный файл успешно прочитан\n");
    return b;
}

int commandLine(char *line, bloom *b, char *fileName) {
    SetConsoleOutputCP(CP_UTF8);
    scanf("%s", line);
    if (line[0] != '-' || (line[1] != 'a' && line[1] != 'c' && line[1] != 'e' && line[1] != 'h')) errors(8, fileName);
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
                printf("Элемент: %c успешно добавлен\n", line[3]);
            } else errors(9, fileName);
        } else errors(10, fileName);
    }
    if (line[0] == '-' && line[1] == 'c') {
        if (strlen(line) == 4) {
            if (contains(&line[3], b) == 1) printf("Элемент: %c возможно есть\n", line[3]);
            else printf("Элемента: %c точно нет\n", line[3]);
        } else errors(10, fileName);
    }
    return 1;
}