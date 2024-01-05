#pragma once

struct Command
{
    char* prefix;
    char* description;
    char* example;
};

struct Command commands[]
{
    {
        "HELP",
        "Shows info about commands",
        "HELP",
    },
    {
        "ECHO",
        "Echoes out given text",
        "ECHO <TEXT>",
    }
}