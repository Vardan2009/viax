#include "lib.h"


void strcpy(char *dest, const char *src) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') {
        i++;
    }
}

int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void strip_whitespace(char* str, char* result) {
   
    while (*str && is_whitespace(*str)) {
        str++;
    }

    if (*str == '\0') {
        *result = '\0';
        return;
    }

   
    const char *end = str;
    while (*end) {
        end++;
    }
    end--;

    
    while (end > str && is_whitespace(*end)) {
        end--;
    }
    
    
    while (str <= end) {
        *result++ = *str++;
    }
    *result = '\0'; 
}

void reverse(char *str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void int_to_string(int num, char *str) {
    int i = 0;
    int isNegative = 0;
    
    if(num == 0)
    {
        strcpy(str,"0");
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    // Add negative sign if necessary
    if (isNegative)
        str[i++] = '-';

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string
    reverse(str, i);
}

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

int strcmp_partial(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (s1[i] != s2[i])
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        if (s1[i] == '\0')  // Reached the end of either string
            return 0;
    }
    return 0; // Strings are equal up to n characters
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

char* touppercase(char* s, char* result) {
    char* originalResult = result;

    while (*s != '\0') {
        if (*s >= 'a' && *s <= 'z') {
            *result = *s - 32;
        } else {
            *result = *s;
        }

        ++s;
        ++result;
    }

    *result = '\0'; // Null-terminate the result string

    return originalResult;
}

void memcpy(void *dest, void *src, size_t n) {
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n-- > 0) {
        *p++ = (unsigned char)c;
    }
    return s;
}