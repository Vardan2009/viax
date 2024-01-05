//VIAX Operating System Kernel
//Writeen by Vardan Petrosyan
// 1/6/24 //

//HELLO C!
#include "print.h"
#include "keyboard.h"
#include "lib.h"
#include "commands.h"

char* logo = " _    _________   _  __\n"
             "| |  / /  _/   | | |/ /\n"
             "| | / // // /| | |   / \n"
             "| |/ // // ___ |/   |  \n"
             "|___/___/_/  |_/_/|_|  \n";
char* version = "0.0.1";



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

void parse_command_old(char* input)
{
   if(strcmp(input,"INFO") == 0)
   {
      info();
   }
   else if(strcmp(input,"BEST OPERATING SYSTEM OF ALL TIME") == 0)
   {
      print_str("Thank you :)");
   }
   else if(strcmp(input,"CLS") == 0)
   {
      print_clear();
   }
   else
   {
      print_error("SYNTAX ERROR");
   }
}


void strsplit(const char* input, char delimiter, char*** tokens, size_t* token_count) {
    // Count the number of tokens
    size_t count = 1;  // At least one token
    const char* ptr = input;
    while (*ptr != '\0') {
        if (*ptr == delimiter) {
            count++;
        }
        ptr++;
    }

    // Allocate memory for tokens
    *tokens = (char**)malloc(count * sizeof(char*));
    if (*tokens == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize variables for tokenization
    size_t token_index = 0;
    size_t token_length = 0;

    // Tokenize the input string
    ptr = input;
    while (*ptr != '\0') {
        if (*ptr == delimiter) {
            // Allocate memory for the token and copy the characters
            (*tokens)[token_index] = (char*)malloc((token_length + 1) * sizeof(char));
            if ((*tokens)[token_index] == NULL) {
                // Handle memory allocation failure
                // You may want to free previously allocated memory before returning
                return;
            }

            // Copy characters to the token
            for (size_t i = 0; i < token_length; i++) {
                (*tokens)[token_index][i] = input[token_index * (token_length + 1) + i];
            }
            (*tokens)[token_index][token_length] = '\0';

            // Move to the next token
            token_index++;
            token_length = 0;
        } else {
            token_length++;
        }

        ptr++;
    }

    // Allocate memory for the last token and copy the characters
    (*tokens)[token_index] = (char*)malloc((token_length + 1) * sizeof(char));
    if ((*tokens)[token_index] == NULL) {
        // Handle memory allocation failure
        // You may want to free previously allocated memory before returning
        return;
    }
    for (size_t i = 0; i < token_length; i++) {
        (*tokens)[token_index][i] = input[token_index * (token_length + 1) + i];
    }
    (*tokens)[token_index][token_length] = '\0';

    // Set the token count
    *token_count = count;
}

void parse_command(char* input)
{
   char** tokens;
   size_t token_count;
   strsplit(input,' ',&tokens,&token_count);
   if(tokens[0] == "INFO")
   {
      info();
   }
   else if(tokens[0] == "ECHO")
   {
      for (size_t i = 1; i < token_count; i++) {
        print_str_end(tokens[i],' ');
      }
      print_str("\0");
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
    print_str_end(">>>",' ');
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_BLACK);
    char* input = scanstring();
    if(strcmp(input,"") ==0) continue;
    else if(strcmp(input,"EXIT") == 0) return;
    else parse_command(input);
   }
}
