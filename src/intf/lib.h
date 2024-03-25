#pragma once
#define MAX_STRING_SIZE 100


int is_whitespace(char c);

void strip_whitespace(char* str,char* result);

void int_to_string(int num, char *str);

int strcmp(char* str1,char* str2);

void splitString(char* str, char delimiter, char** result, int* resultSize);

char* tolowercase(char* s,char* result);