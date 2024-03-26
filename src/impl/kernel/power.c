#include "power.h"



void outb_c(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint8_t inb_c(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}


void cpu_halt()
{
  print_str("CPU Halted");
  halt_cpu_asm();
}

void reboot()
{
    uint8_t temp;
 
    asm volatile ("cli"); /* disable all interrupts */
 
    /* Clear all keyboard buffers (output and command buffers) */
    do
    {
        temp = inb_c(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb_c(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb_c(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
    loop:
      asm volatile ("hlt"); /* if that didn't work, halt the CPU */
      goto loop; /* if a NMI is received, halt again */
}