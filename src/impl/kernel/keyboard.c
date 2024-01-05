#include "keyboard.h"
#include "print.h"
#define MAX_STRING_SIZE 100

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

char scanchar()
{
    char res = get_char_from_code(get_scancode());
    return res;
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