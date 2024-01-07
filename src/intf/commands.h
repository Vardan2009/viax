#pragma once

struct Command
{
    char* prefix;
    char* description;
    char* example;
};

extern int commands_len;
extern struct Command commands[];