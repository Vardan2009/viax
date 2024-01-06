#include <stddef.h>
#include "print.h"
#include "keyboard.h"


#define MAX_STRING_SIZE 100

int shifted = 0;

int keysLength = 74;
struct Key keys[] = {
    {'A', 0x1E}, {'B', 0x30}, {'C', 0x2E}, {'D', 0x20}, {'E', 0x12},
    {'F', 0x21}, {'G', 0x22}, {'H', 0x23}, {'I', 0x17}, {'J', 0x24},
    {'K', 0x25}, {'L', 0x26}, {'M', 0x32}, {'N', 0x31}, {'O', 0x18}, //25
    {'P', 0x19}, {'Q', 0x10}, {'R', 0x13}, {'S', 0x1F}, {'T', 0x14},
    {'U', 0x16}, {'V', 0x2F}, {'W', 0x11}, {'X', 0x2D}, {'Y', 0x15},
    {'Z', 0x2C}, //1
    {'0', 0x0B}, {'1', 0x02}, {'2', 0x03}, {'3', 0x04}, {'4', 0x05},
    {'5', 0x06}, {'6', 0x07}, {'7', 0x08}, {'8', 0x09}, {'9', 0x0A},
    {'!', 0x1E}, {'@', 0x30}, {'#', 0x2E}, {'$', 0x20}, {'%', 0x12}, //30
    {'^', 0x21}, {'&', 0x22}, {'*', 0x23}, {'(', 0x17}, {')', 0x24},
    {'-', 0x25}, {'_', 0x26}, {'+', 0x32}, {'=', 0x31}, {'[', 0x18},
    {']', 0x19}, {'{', 0x10}, {'}', 0x13}, {';', 0x1F}, {':', 0x14},
    {'\'', 0x16}, {'\"', 0x2F}, {',', 0x11}, {'.', 0x2D}, {'?', 0x15},
    {'/', 0x2C}, {'\\', 0x2B}, {'|', 0x2B}, {'~', 0x29}, {'`', 0x29}, //18
    {'<', 0x33}, {'>', 0x34}, {'/', 0x35}, {'_', 0x33}, {' ', 0x39},
    {' ', 0x39},{'\b', 0x0E}, {'\n', 0x1C}
};


uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a"(data) : "d"(port));
    return data;
}



int is_keyboard_data_available() {
    return (inb(0x64) & 0x01);
}

uint8_t get_scancode() {
    uint8_t scancode;
    
    if(is_keyboard_data_available())
    {
        do {
            scancode = inb(0x60);
        } while ((scancode & 0x80) != 0);
    }
  

    return scancode;
}
char get_char_from_code(uint8_t code) {
    for (size_t i = 0; i < keysLength; ++i) {
        if (keys[i].Code == code) {
            return keys[i].Char;
        }
    }

    char* myString; 
    return '\0';
}

char scanchar() {
    uint8_t charCode = get_scancode();
    char e = get_char_from_code(charCode);
    return e;
}

char* scanstring() {
    char* result = "";
    if (result == NULL) {
        print_error("MEMORY ALLOCATION ERROR AT SCANSTRING");
        return NULL;
    }

    int size = 0;
    while (1) {
        char e = scanchar(); 
        if(!e) continue;
        if (e == '\n') {
            print_char('\n');
            break;
        }
        if (e == '\b') {
            if (size > 0) {
                print_backspace();
                size--;
                result[size] = '\0';
            }
        }
        else {
            print_char(e);
            if (size < MAX_STRING_SIZE - 1) { 
                result[size] = e;
                size++;
             
            } else {
                print_error("INPUT BUFFER OVERFLOW");
                break;
            }
        }

    }
    result[size] = '\0';  
    return result;
}