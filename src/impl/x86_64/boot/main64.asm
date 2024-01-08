global long_mode_start
global shutdownasm
global rebootasm
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

shutdownasm:
    mov eax, 0x0           ; AH=0 means shutdown
    mov ebx, 0x0           ; BX=0 means power off
    int 0x16 
    ret

rebootasm:
    ; ACPI reboot
    mov ax, 0x5307
    mov bx, 0x0001
    mov cx, 0x0001
    int 0x15
    ret


