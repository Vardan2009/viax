#include <stdint.h>

#pragma once


struct Key {
    char Char;
    char ShiftedChar;
    uint8_t Code;
};

char* scanstring();
uint8_t inb(uint16_t port);
int is_keyboard_data_available();
uint8_t get_scancode();
struct Key get_char_from_code(uint8_t code);
struct Key scanchar();
char* scanstring();