#pragma once

struct Command
{
    char* prefix;
    char* description;
    char* example;
};

extern struct Command commands[];