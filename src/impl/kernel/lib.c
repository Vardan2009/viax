#include "lib.h"

int strcmp(char* str1, char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    // Check for the end of both strings
    if (*str1 == '\0' && *str2 == '\0') {
        return 0; // Strings are equal
    } else if (*str1 == '\0') {
        return -1; // str1 is shorter than str2
    } else {
        return 1;  // str2 is shorter than str1
    }
}

void splitString(char* str, char delimiter, char** result, int* resultSize) {
    int index = 0;
    *resultSize = 0;

    // Handle the case where there's no delimiter in the string
    result[index++] = str;
    (*resultSize)++;

    while (*str != '\0') {
        if (*str == delimiter) {
            *str = '\0';
            result[index++] = str + 1;
            (*resultSize)++;
        }
        str++;
    }
}
char* tolowercase(char* s, char* result) {
    char* originalResult = result;

    while (*s != '\0') {
        if (*s >= 'A' && *s <= 'Z') {
            *result = *s + 32;
        } else {
            *result = *s;
        }

        ++s;
        ++result;
    }

    *result = '\0'; // Null-terminate the result string

    return originalResult;
}