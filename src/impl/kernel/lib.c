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