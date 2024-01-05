#include "keyboard.h"
#include "print.h"

#define MAX_STRING_SIZE 100

uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a"(data) : "d"(port));
    return data;
}

// Function to check if the keyboard has data available
int is_keyboard_data_available() {
    return (inb(0x64) & 0x01);
}

uint8_t get_scancode() {
    
    while (!is_keyboard_data_available()) {
     
    }

    // Read the scancode from the keyboard
    return inb(0x60);
}

char get_char_from_scancode(uint8_t scancode) {
    
    switch (scancode) {
        case 0x1E: return 'A';
        case 0x30: return 'B';
        case 0x2E: return 'C';
        case 0x20: return 'D';
        case 0x12: return 'E';
        case 0x21: return 'F';
        case 0x22: return 'G';
        case 0x23: return 'H';
        case 0x17: return 'I';
        case 0x24: return 'J';
        case 0x25: return 'K';
        case 0x26: return 'L';
        case 0x32: return 'M';
        case 0x31: return 'N';
        case 0x18: return 'O';
        case 0x19: return 'P';
        case 0x10: return 'Q';
        case 0x13: return 'R';
        case 0x1F: return 'S';
        case 0x14: return 'T';
        case 0x16: return 'U';
        case 0x2F: return 'V';
        case 0x11: return 'W';
        case 0x2D: return 'X';
        case 0x15: return 'Y';
        case 0x2C: return 'Z';

        // Numbers
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';

        // Special characters
        case 0x1C: return '\n';  // Enter key
        case 0x0E: return '\b';  // Backspace key
        case 0x39: return ' ';   // Spacebar

        // Add more cases for other keys as needed
        // ...

        default:
            // Return 0 for unsupported scancodes
            return NULL;
    }
}

char scanchar()
{
    char res = get_char_from_scancode(get_scancode());
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
        char e = scanchar(); // Assuming scanchar() is a function you have defined elsewhere
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
            if (size < MAX_STRING_SIZE - 1) { // Ensure not to overflow the buffer
                result[size] = e;
                size++;
             
            } else {
                print_error("INPUT BUFFER OVERFLOW");
                break;
            }
        }

    }
    result[size] = '\0';  // Null-terminate the string after adding a character
    return result;
}