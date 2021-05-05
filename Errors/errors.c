#include <stdio.h>
#include "errors.h"
#include <windows.h>

void errors(int err, char *string) {
    SetConsoleOutputCP(CP_UTF8);
    if (err == 1) {
        printf("\nОшибка № %d: Неккоректный вид командной строки. Ожидалось: ...\\Bloom_filter.exe *Путь файла конфигурации*\n", err);
        exit(err);
    }
    if (err == 2) {
        printf("\nОшибка № %d: Не удалось прочитать файл: %s. Возможно его не существует\n", err, string);
        exit(err);
    }
    if (err == 3) {
        printf("\nОшибка № %d: Файл: %s неправильно задан. Ожидалось:\nFilter length:"
               "\nNumber of elements:\nElements:\nКоличество строк больше трех", err, string);
        exit(err);
    }
    if (err == 4) {
        printf("\nОшибка № %d: Раздел: %s неправильно задан. Ожидалось:\nFilter length:\nNumber of elements:"
               "\nElements:", err, string);
        exit(err);
    }
    if (err == 5) {
        printf("\nОшибка № %d: Неправильно задана длина битового поля или количество элементов. Эти значения должны быть больше нуля\n", err);
        exit(err);
    }
    if (err == 6) {
        printf("\nОшибка № %d: Битовое поле слишком мало для такого количества элементов\n", err);
        exit(err);
    }
    if (err == 7) {
        printf("\nОшибка № %d: Некорректный входной элемент, длина больше одного\n", err);
        exit(err);
    }
    if (err == 8) {
        printf("\nОшибка № %d: Некорректный ключ командной строки. Для просмотра режимов работы, введите ключ: -h\n", err);
        exit(err);
    }
    if (err == 9) {
        printf("\nОшибка № %d: Больше нельзя добавить элемент\n", err);
        exit(err);
    }
    if (err == 10) {
        printf("\nОшибка № %d: Не задан элемент для добавления или проверки\n", err);
        exit(err);
    }
    if (err == 11) {
        printf("\nОшибка № %d: Ошибка выделения памяти под %s\n", err, string);
        exit(err);
    }
    if (err == 12) {
        printf("\nОшибка № %d: Ошибка перераспределения памяти под %s\n", err, string);
        exit(err);
    }
}
