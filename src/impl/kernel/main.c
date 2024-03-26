//VIAX Operating System Kernel
//Writeen by Vardan Petrosyan
// 1/6/24 //

//HELLO C!

#include "print.h"
#include "keyboard.h"
#include "lib.h"
#include "commands.h"
#include "power.h"

#include "main.h"
#define MAX_STRING_SIZE 100


void parse_command(char* input)
{
   char* args[100];
   int args_len;
   splitString(input, ' ', args, &args_len);
   char cmd[MAX_STRING_SIZE];
   tolowercase(args[0],cmd);
   struct Command* fcmd = fetch_command_by_alias(cmd);
   if(fcmd != NULL) {
      fcmd->execute(args, args_len);
   }
}

void viax_kernel_main()
{
   print_clear();
   cmd_info();
   print_str("Welcome to the VIAX Operating System!\nUse 'help' for command list");
   while(1)
   {
    print_set_color(PRINT_COLOR_YELLOW,PRINT_COLOR_BLACK);
    print_str_end("-$"," ");
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    char* rawinput = scanstring();
    char input[MAX_STRING_SIZE];
    strip_whitespace(rawinput,input);
    // any input starting with a colon is a comment
    if(strcmp(input,"") ==0 || input[0] == ':') continue;
    else parse_command(input);
   }
}

