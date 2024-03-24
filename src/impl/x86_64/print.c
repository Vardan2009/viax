#include "print.h"
#include <stdint.h>

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char
{
    uint8_t character;
    uint8_t color;
};


struct Char* buffer = (struct Char* ) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;


struct Char empty = (struct Char){
    character: ' ',
    color:PRINT_COLOR_WHITE,
};

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void move_cursor() {
    uint16_t position = row * NUM_COLS + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void clear_row(size_t row)
{
    for (size_t col = 0;col<NUM_COLS;col++)
    {
        buffer[col+NUM_COLS*row] = empty;
    }
}

void print_newline()
{
    col = 0;
    if(row < NUM_ROWS - 1)
    {
        row++;
        return;
    }
    for(size_t r = 1; r < NUM_ROWS; r++)
    {
        for(size_t c = 0; c < NUM_COLS; c++)
        {
            struct Char character = buffer[c + NUM_COLS * r];
            buffer[c + NUM_COLS * (r - 1)] = character;
        }
    }
    clear_row(NUM_ROWS - 1);
}

void print_clear()
{
   for(size_t i = 0;i<NUM_ROWS;i++)
   {
    clear_row(i);
   }
   row = 0;
   col = 0;
   move_cursor();
}

void print_char(char character)
{
    for(size_t i = 0;i<NUM_ROWS;i++)
    {
        if(character == '\n')
        {
            print_newline();
            return;
        }
    }

    if(col>NUM_COLS)
    {
        print_newline();
    }
    buffer[col+NUM_COLS*row] = (struct Char)
    {
        character:(uint8_t)character,
        color:color,
    };
    col++;
    move_cursor();
}

void print_backspace()
{
    col--;
    if(col <= 0)
    {
        col = NUM_COLS;
        row--;
    }
    print_char(' ');
    col--;
    move_cursor();
}

void print_str(char* str)
{
    for(size_t i =0;1;i++)
    {
        char character = (uint8_t)str[i];
        if(character == '\0')
        {
            print_newline();
            return;
        }
        print_char(character);
    }
}

void print_str_end(char* str,char* end)
{
    for(size_t i =0;1;i++)
    {
        char character = (uint8_t)str[i];
        if(character == '\0')
        {
            for(size_t i = 0;1;i++)
            {
                if((uint8_t)end[i] == '\0') break;
                print_char((uint8_t)end[i]);
            }
            return;
        }
        print_char(character);
    }
}

void print_error(char* msg)
{
    uint8_t cached_color = color;
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_RED);
    print_str_end("[ERR]"," ");
    print_str(msg);
    color = cached_color;
}

void print_error_add(char* msg,char* additional)
{
    uint8_t cached_color = color;
    print_set_color(PRINT_COLOR_WHITE,PRINT_COLOR_RED);
    print_str_end("[ERR]"," ");
    print_str_end(msg,"");
    print_str(additional);
    color = cached_color;
}

void print_set_color(uint8_t foreground,uint8_t background)
{
    color = foreground+(background<<4);
}

