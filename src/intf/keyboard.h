#include <stdint.h>

#pragma once


struct Key {
    char Char;
    uint8_t Code;
};


char scanchar();
char* scanstring();
uint8_t inb(uint16_t port);
int is_keyboard_data_available();
uint8_t get_scancode();
char get_char_from_code(uint8_t code);
char scanchar();
char* scanstring();