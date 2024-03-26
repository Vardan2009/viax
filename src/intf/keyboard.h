#pragma once

#include <stdint.h>



#define MAX_STRING_SIZE 100
#define MAX_HISTORY_LENGTH 20

struct Key {
    char Char;
    char ShiftedChar;
    uint8_t Code;
};


extern char command_history [MAX_HISTORY_LENGTH][MAX_STRING_SIZE];
extern int history_length;

char* scanstring();
char* scancmd();
uint8_t inb(uint16_t port);
int is_keyboard_data_available();
uint8_t get_scancode();
struct Key get_char_from_code(uint8_t code);
struct Key scanchar();
char* scanstring();