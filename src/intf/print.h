#pragma once

#include <stdint.h>
#include <stddef.h>



enum {
    PRINT_COLOR_BLACK = 0,
	PRINT_COLOR_BLUE = 1,
	PRINT_COLOR_GREEN = 2,
	PRINT_COLOR_CYAN = 3,
	PRINT_COLOR_RED = 4,
	PRINT_COLOR_MAGENTA = 5,
	PRINT_COLOR_BROWN = 6,
	PRINT_COLOR_LIGHT_GRAY = 7,
	PRINT_COLOR_DARK_GRAY = 8,
	PRINT_COLOR_LIGHT_BLUE = 9,
	PRINT_COLOR_LIGHT_GREEN = 10,
	PRINT_COLOR_LIGHT_CYAN = 11,
	PRINT_COLOR_LIGHT_RED = 12,
	PRINT_COLOR_PINK = 13,
	PRINT_COLOR_YELLOW = 14,
	PRINT_COLOR_WHITE = 15,
};

void outb(uint16_t port, uint8_t value);
void move_cursor();
void print_clear();
void print_newline();
void print_char(char ch);
void print_str_end(char* str,char* end);
void print_str(char* str);
void print_set_color(uint8_t foreground,uint8_t background);
void print_error(char* msg);
void print_error_add(char* msg,char* additional);
void print_backspace();