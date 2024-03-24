#pragma once

#define MAX_ALIAS_COUNT 10

typedef void (*FunctionPtr)(char**,int);

struct Command
{
    char* prefix;
    char* description;
    char* example;
    char* aliases[MAX_ALIAS_COUNT];
    int alias_count;
    FunctionPtr execute;
};

extern int commands_len;

struct Command* fetch_command_by_alias(char* alias);

extern struct Command commands[];