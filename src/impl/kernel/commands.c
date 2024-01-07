#include <stddef.h>
#include "print.h" 
#include "commands.h"


int commands_len = 5;
struct Command commands[] =
{
    {
        "HELP",
        "Shows info about commands",
        "Additional Parameters:\nhelp <cmdName>",
    },
    {
        "ECHO",
        "Echoes out given text",
        "Usage: ECHO <TEXT>",
    },
    {
        "INFO",
        "Shows OS Info",
        "Additional Parameters:\ninfo ver"
    },
    {
        "OFF",
        "Shutdowns PC",
        "Usage: OFF"
    },
    {
        "REBOOT",
        "Reboots PC",
        "Usage: REBOOT"
    }
};
