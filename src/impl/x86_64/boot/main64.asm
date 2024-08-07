global long_mode_start
global halt_cpu_asm
extern viax_kernel_main

section .text
bits 64

long_mode_start:
    mov ax,0
    mov ss,ax
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    call viax_kernel_main
    hlt

halt_cpu_asm:
    ; CPU Halt
    cli
    hlt