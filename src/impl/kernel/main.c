#include "print.h"

//HELLO C!
void viax_kernel_main()
{
   print_clear();
   print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
   print_str("Welcome to ");
   print_set_color(PRINT_COLOR_BLUE,PRINT_COLOR_BLACK);
   print_str("VIAX\n");
}