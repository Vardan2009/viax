#include "power.h"

void shutdown() {
    asm volatile(
        "call shutdown\n"
    );
}

void reboot() {
    asm volatile(
        "call reboot\n"
    );
}