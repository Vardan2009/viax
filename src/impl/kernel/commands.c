#include <stddef.h>
#include "print.h" 
#include "commands.h"
#include "keyboard.h"
#include "power.h"
#include "cpu.h"


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
                  "| |/ // // / | |/   |  \n"
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
            print_str_end(commands[i].prefix,i==commands_len-1?"":" / ");
         }
         print_str("\nUse help <cmdName> for detailed info about each one");
    }
    else
    {
        struct Command *selected = fetch_command_by_alias(args[1]);
       
        if(selected != NULL)
        {
            print_str(selected -> prefix);
            print_str(selected -> description);
            print_str(selected -> example);
            print_str_end("Aliases:"," ");
            for(int i =0;i<selected->alias_count;i++)
            {
                print_str_end(selected->aliases[i],i==selected->alias_count-1?"":", ");
            }
            print_newline();
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

void cmd_halt(char* args[100],int args_len)
{
    cpu_halt();
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

void cmd_sysfetch(char* args[100],int args_len)
{
    detect_cpu();
}

void cmd_history(char* args[100],int args_len)
{
    if(args_len == 1)
    {
        for(int i =0;i<history_length;i++)
        {
            char* istr[MAX_STRING_SIZE];
            int_to_string(i,istr);
            print_str_end(istr,": ");
            print_str(command_history[i]);
        }
    }
    else
    {
        if(strcmp(args[1],"clear") == 0)
        {
            for(int i =0;i<history_length;i++)
            {
               strcpy(command_history[i],"");
            }
            history_length = 0;
        }
    }
}

struct Command* fetch_command_by_alias(char* alias)
{
   for(int i =0;i<commands_len;i++)
   {
      for(int j = 0;j<commands[i].alias_count;j++)
      {
         if(strcmp(alias,commands[i].aliases[j]) == 0)
         {
          
            return &commands[i];
         }
      }
   }
   print_error_add("No such command: ",alias);
   return NULL;
}


int commands_len =9;
struct Command commands[] =
{
    {
        "HELP",
        "Shows info about commands",
        "Additional Parameters:\nhelp <cmdName>",
        {"help","explain"},2,
        &cmd_help
    },
    {
        "ECHO",
        "Echoes out given text",
        "Usage: ECHO <TEXT>",
        {"echo","out"},2,
        &cmd_echo
    },
    {
        "INFO",
        "Shows OS Info",
        "Additional Parameters:\nver",
        {"info","viax"},2,
        &cmd_info
    },
    {
        "HALT",
        "halts the CPU",
        "Usage: HALT",
        {"halt","cpuhalt"},2,
        &cmd_halt
    },
    {
        "REBOOT",
        "Reboots PC",
        "Usage: REBOOT",
        {"reboot","renew","restart"},3,
        &cmd_reboot
    },
    {
        "CLEAR",
        "Clears Screen",
        "Usage: CLS",
        {"cls","clear","clr"},3,
        &cmd_cls
    },
    {
        "BRAINF",
        "Compiles brainf code",
        "Usage: BF <code>",
        {"bf","brainf"},2,
        &cmd_bf
    },
    {
        "SYSFETCH",
        "Fetches system info",
        "Usage: SYSFETCH",
        {"sysfetch"},1,
        &cmd_sysfetch
    },
    {
        "HISTORY",
        "Views command History",
        "Usage: HISTORY",
        {"history","hist"},2,
        &cmd_history
    }
};


