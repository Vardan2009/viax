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

char* logo = " _    _________   _  __\n"
                  "| |  / /  _/   | | |/ /\n"
                  "| | / // // /| | |   / \n"
                  "| |/ // // ___ |/   |  \n"
                  "|___/___/_/  |_/_/|_|  \n";

char* version = "0.4 Alpha";
void info()
{
    
    

    print_set_color(PRINT_COLOR_LIGHT_CYAN,PRINT_COLOR_BLACK);
    print_str(logo);
    print_set_color(PRINT_COLOR_DARK_GRAY,PRINT_COLOR_BLACK);
    print_str_end("Version:",' ');
    print_set_color(PRINT_COLOR_YELLOW,PRINT_COLOR_BLACK);
    print_str(version);
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    print_str("Created by Vardan Petrosyan\n");
}


void parse_command(char* input)
{
   char* args[100];
   int args_len;
   splitString(input, ' ', args, &args_len);
   char cmd[MAX_STRING_SIZE];
   tolowercase(args[0],cmd);
   if(strcmp(cmd,"info") == 0)
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
   else if(strcmp(cmd,"help") == 0)
   {
      if(args_len == 1)
      {
         print_str("All avaliable Commands: ");
         for(int i =0;i<commands_len;i++)
         {
            print_str_end(commands[i].prefix,' ');
         }
         print_str("\nUse help <cmdName> for detailed info about each one");
      }
      else
      {
         struct Command selected = {'NULL','NULL','NULL'};
         for(int i =0;i<commands_len;i++)
         {
           char a[MAX_STRING_SIZE];
           char b[MAX_STRING_SIZE];
           tolowercase(commands[i].prefix,a);
           tolowercase(args[1],b);
         
           if(strcmp(a,b) == 0)
           {
               selected = commands[i];
               break;
           }
         }
         if(selected.prefix != 'NULL')
         {
            print_str(selected.prefix);
            print_str(selected.description);
            print_str(selected.example);
         }
         else
         {
            print_error("FAILED TO FETCH CMD INFO");
         }
      }
   }
   else if(strcmp(cmd,"echo") == 0)
   {
      for (int i = 1; i < args_len; i++) {
        print_str_end(args[i],' ');
      }
      print_str("\0");
   }
   else if(strcmp(cmd,"cls") == 0)
   {
      print_clear();
   }
   else if(strcmp(cmd,"off") == 0)
   {
      shutdown();
   }
   else if(strcmp(cmd,"reboot") == 0)
   {
      reboot();
   }
   else
   {
      print_error("UNKNOWN COMMAND");
   }
}

void viax_kernel_main()
{
   print_clear();
   print_str("Welcome to the VIAX Operating System!");
   info();
   while(1)
   {
    print_set_color(PRINT_COLOR_YELLOW,PRINT_COLOR_BLACK);
    print_str_end("",'$');
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    char* input = scanstring();
    if(strcmp(input,"") ==0) continue;
    else parse_command(input);
   }
}

