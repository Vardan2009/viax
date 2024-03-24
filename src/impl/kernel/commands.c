#include <stddef.h>
#include "print.h" 
#include "commands.h"
#include "keyboard.h"




//bf language
#define TAPE_SIZE 30000

#define INC_PTR '>'
#define DEC_PTR '<'
#define INC_VAL '+'
#define DEC_VAL '-'
#define LOOP_START '['
#define LOOP_END ']'
#define OUTPUT '.'
#define INPUT ','

unsigned char tape[TAPE_SIZE] = {0};
unsigned char *ptr = tape;

const char* logo =" _    _________   _  __\n"
                  "| |  / /  _/   | | |/ /\n"
                  "| | / // // /| | |   / \n"
                  "| |/ // // ___ |/   |  \n"
                  "|___/___/_/  |_/_/|_|  \n";

const char* version = "0.5 Alpha";


void info()
{
    print_set_color(PRINT_COLOR_LIGHT_CYAN,PRINT_COLOR_BLACK);
    print_str(logo);
    print_set_color(PRINT_COLOR_DARK_GRAY,PRINT_COLOR_BLACK);
    print_str_end("Version:"," ");
    print_set_color(PRINT_COLOR_YELLOW,PRINT_COLOR_BLACK);
    print_str(version);
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    print_str("Created by Vardan Petrosyan\n");
}

void cmd_help(char* args[100],int args_len)
{
    if(args_len == 1)
    {
         print_str("All avaliable Commands: ");
         for(int i =0;i<commands_len;i++)
         {
            print_str_end(commands[i].prefix," / ");
         }
         print_str("\nUse help <cmdName> for detailed info about each one");
    }
    else
    {
        struct Command *selected = NULL;
        for(int i =0;i<commands_len;i++)
        {
           char a[MAX_STRING_SIZE];
           char b[MAX_STRING_SIZE];
           tolowercase(commands[i].prefix,a);
           tolowercase(args[1],b);
         
           if(strcmp(a,b) == 0)
           {
               selected = &commands[i];
               break;
           }
        }
        if(selected != NULL)
        {
            print_str(selected -> prefix);
            print_str(selected -> description);
            print_str(selected -> example);
        }
        else
        {
            print_error("FAILED TO FETCH CMD INFO");
        }
    }
}

void cmd_info(char* args[100],int args_len)
{
      if(args_len ==2)
      {
         if(strcmp(args[1],"ver") == 0)
         {
            print_str(version);
         }
         else
         {
            print_str("USAGE: info < --ver:optional >");
         }
      }
      else
      {
         info();
      }
}

void cmd_echo(char* args[100],int args_len)
{
    for (int i = 1; i < args_len; i++) {
        print_str_end(args[i]," ");
    }
    print_str("\0");
}

void cmd_off(char* args[100],int args_len)
{
    shutdown();
}

void cmd_reboot(char* args[100],int args_len)
{
    reboot();
}

void cmd_bf(char* args[100],int args_len)
{
    char* code = args[1];
    while (*code) {
        switch (*code) {
            case INC_PTR:
                ++ptr;
                break;
            case DEC_PTR:
                --ptr;
                break;
            case INC_VAL:
                ++(*ptr);
                break;
            case DEC_VAL:
                --(*ptr);
                break;
            case OUTPUT:
                print_char(*ptr);
                break;
            case INPUT:
                *ptr = scanchar().Char;
                break;
            case LOOP_START:
                if (*ptr == 0) {
                    int loop_count = 1;
                    while (loop_count != 0) {
                        ++code;
                        if (*code == LOOP_START) {
                            ++loop_count;
                        } else if (*code == LOOP_END) {
                            --loop_count;
                        }
                    }
                }
                break;
            case LOOP_END:
                if (*ptr != 0) {
                    int loop_count = 1;
                    while (loop_count != 0) {
                        --code;
                        if (*code == LOOP_START) {
                            --loop_count;
                        } else if (*code == LOOP_END) {
                            ++loop_count;
                        }
                    }
                }
                break;
        }
        ++code;
    }
    print_newline();
}

void cmd_cls(char* args[100],int args_len)
{
    print_clear();
}

int commands_len =7;
struct Command commands[] =
{
    {
        "HELP",
        "Shows info about commands",
        "Additional Parameters:\nhelp <cmdName>",
        "help",
        &cmd_help
    },
    {
        "ECHO",
        "Echoes out given text",
        "Usage: ECHO <TEXT>",
        "echo",
        &cmd_echo
    },
    {
        "INFO",
        "Shows OS Info",
        "Additional Parameters:\ninfo ver",
        "info",
        &cmd_info
    },
    {
        "OFF",
        "Shutdowns PC",
        "Usage: OFF",
        "off",
        &cmd_off
    },
    {
        "REBOOT",
        "Reboots PC",
        "Usage: REBOOT",
        "reboot",
        &cmd_reboot
    },
    {
        "CLEAR",
        "Clears Screen",
        "Usage: CLS",
        "cls",
        &cmd_cls
    },
    {
        "BRAINF",
        "Compiles brainf code",
        "usage bf <code>",
        "bf",
        &cmd_bf
    }
};
