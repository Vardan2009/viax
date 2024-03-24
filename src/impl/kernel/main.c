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

   int executed = 0;
   for(int i =0;i<commands_len;i++)
   {
      if(strcmp(cmd,commands[i].alias) == 0)
      {
         executed = 1;
         commands[i].execute(args,args_len);
      }
   }
   if(executed ==0)
   {
      print_error("No such command");
   }

}

void viax_kernel_main()
{
   print_clear();
   cmd_info();
   print_str("Welcome to the VIAX Operating System!");
   while(1)
   {
    print_set_color(PRINT_COLOR_YELLOW,PRINT_COLOR_BLACK);
    print_str_end("-","$");
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    char* input = scanstring();
    if(strcmp(input,"") ==0) continue;
    else parse_command(input);
   }
}

