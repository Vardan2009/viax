#pragma once

typedef void (*FunctionPtr)(char**,int);

struct Command
{
    char* prefix;
    char* description;
    char* example;
    char* alias;
    FunctionPtr execute;
};

extern int commands_len;
extern struct Command commands[];