#pragma once
#define MAX_STRING_SIZE 100

#include <stddef.h>

void strcpy(char *dest, const char *src);

int is_whitespace(char c);

void strip_whitespace(char* str,char* result);

void int_to_string(int num, char *str);

int strcmp(char* str1,char* str2);

int strcmp_partial(const char *s1, const char *s2, size_t n);

void splitString(char* str, char delimiter, char** result, int* resultSize);

char* tolowercase(char* s,char* result);

char* touppercase(char* s, char* result);

void memcpy(void *dest, void *src, size_t n);

void *memset(void *s, int c, size_t n);

