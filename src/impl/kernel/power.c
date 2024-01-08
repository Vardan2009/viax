#include "power.h"

extern int shutdownasm();
extern int rebootasm();


void shutdown() {
  shutdownasm();
}

void reboot() {
   rebootasm();
}