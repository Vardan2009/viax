#include <stddef.h>
#include "print.h"
#include "keyboard.h"


#define MAX_STRING_SIZE 100

int shifted = 0;

int keysLength = 74;
struct Key keys[] = {
    {'a', 'A', 0x1E}, {'b', 'B', 0x30}, {'c', 'C', 0x2E}, {'d', 'D', 0x20}, {'e', 'E', 0x12},
    {'f', 'F', 0x21}, {'g', 'G', 0x22}, {'h', 'H', 0x23}, {'i', 'I', 0x17}, {'j', 'J', 0x24},
    {'k', 'K', 0x25}, {'l', 'L', 0x26}, {'m', 'M', 0x32}, {'n', 'N', 0x31}, {'o', 'O', 0x18},
    {'p', 'P', 0x19}, {'q', 'Q', 0x10}, {'r', 'R', 0x13}, {'s', 'S', 0x1F}, {'t', 'T', 0x14},
    {'u', 'U', 0x16}, {'v', 'V', 0x2F}, {'w', 'W', 0x11}, {'x', 'X', 0x2D}, {'y', 'Y', 0x15},
    {'z', 'Z', 0x2C}, {'0', ')', 0x0B}, {'1', '!', 0x02}, {'2', '@', 0x03}, {'3', '#', 0x04},
    {'4', '$', 0x05}, {'5', '%', 0x06}, {'6', '^', 0x07}, {'7', '&', 0x08}, {'8', '*', 0x09},
    {'9', '(', 0x0A}, {'!', '!', 0x1E}, {'@', '@', 0x30}, {'#', '#', 0x2E}, {'$', '$', 0x20},
    {'%', '%', 0x12}, {'^', '^', 0x21}, {'&', '&', 0x22}, {'*', '*', 0x23}, {'(', '(', 0x17},
    {')', ')', 0x24}, {'-', '_', 0x25}, {'_', '_', 0x26}, {'+', '+', 0x32}, {'=', '=', 0x31},
    {'[', '{', 0x18}, {']', '}', 0x19}, {'{', '{', 0x10}, {'}', '}', 0x13}, {';', ':', 0x1F},
     {'\'', '\"', 0x16}, {'\"', '\"', 0x2F}, {',', '<', 0x11}, {'.', '>', 0x2D},
    {'/', '?', 0x2C}, {'\\', '|', 0x2B}, {'~', '~', 0x29},
    {'`', '`', 0x29}, {',', '<', 0x33}, {'.', '>', 0x34}, {'/', '?', 0x35}, {'-', '_', 0x33},
    {' ', ' ', 0x39}, {' ', ' ', 0x39}, {'\b', '\b', 0x0E}, {'\n', '\n', 0x1C}
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
    
    while(!is_keyboard_data_available())
    {
        /*do {
           
        } while ((scancode & 0x80) != 0);*/
    }
    scancode = inb(0x60);

    return scancode;
}
struct Key get_char_from_code(uint8_t code) {
    for (size_t i = 0; i < keysLength; ++i) {
        if (keys[i].Code == code) {
            return keys[i];
        }
    }

    char* myString; 
    return (struct Key){'\0','\0',0x00};
}

struct Key scanchar() {
    uint8_t charCode = get_scancode();
    struct Key e = get_char_from_code(charCode);
    return e;
}
int isShifted = 0;
char* scanstring() {
    char* result = "";
    if (result == NULL) {
        print_error("MEMORY ALLOCATION ERROR AT SCANSTRING");
        return NULL;
    }

    int size = 0;
    while (1) {
        uint8_t charCode = get_scancode();
        struct Key e = get_char_from_code(charCode);
        if(charCode == 0x2A)
        {
            isShifted = 1;
            continue;
        }
        if(charCode == 0xAA)
        {
            isShifted = 0;
            continue;
        }
        char capital = e.Char;
        char small = e.ShiftedChar;
        char curch;
        if(isShifted == 0)
            curch = capital;
        else
            curch = small;
        if(!curch) continue;
        if (curch == '\n') {
            print_char('\n');
            break;
        }
        if (curch == '\b') {
            if (size > 0) {
                print_backspace();
                size--;
                result[size] = '\0';
            }
        }
        else {
            print_char(curch);
            if (size < MAX_STRING_SIZE - 1) { 
                result[size] = curch;
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