//VIAX Operating System Kernel
//Writeen by Vardan Petrosyan
// 1/6/24 //

//HELLO C!

#include "print.h"
#include "keyboard.h"
#include "lib.h"
#include "commands.h"

#include "main.h"

void info()
{
    char* logo = " _    _________   _  __\n"
                "| |  / /  _/   | | |/ /\n"
                "| | / // // /| | |   / \n"
                "| |/ // // ___ |/   |  \n"
                "|___/___/_/  |_/_/|_|  \n";
    char* version = "0.0.1";

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
   char* splitParts[100];
   int resultSize;
   splitString(input, ' ', splitParts, &resultSize);
   tolowercase(splitParts[0]);
   if(strcmp(splitParts[0],"info") == 0)
   {
      info();
   }
   else if(strcmp(splitParts[0],"echo") == 0)
   {
      for (int i = 1; i < resultSize; i++) {
        print_str_end(splitParts[i],' ');
      }
      print_str("\0");
   }
   else if(strcmp(splitParts[0],"cls") == 0)
   {
      print_clear();
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
    else if(strcmp(tolowercase(input),"exit") == 0) return;
    else parse_command(input);
   }
}

