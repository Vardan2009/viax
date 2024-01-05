#include "print.h"
#include "keyboard.h"

//HELLO C!
void viax_kernel_main()
{
   print_clear();
   print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
   print_str("Welcome to ");
   print_set_color(PRINT_COLOR_BLUE,PRINT_COLOR_BLACK);
   print_str("VIAX\n");
   print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
   while(1)
   {
    print_str(">>> ");
    char* input = scanstring();
    print_str("You Inputted: ");
    print_str(input);
    print_char('\n');
   }
   
}