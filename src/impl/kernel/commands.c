#include <stddef.h>
#include "print.h" 
#include "commands.h"

struct Command commands[] =
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
};
