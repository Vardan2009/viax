global long_mode_start
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

shutdown:
    ; ACPI shutdown
    mov ax, 0x530E
    mov bx, 0x0001
    int 0x15
    ret

reboot:
    ; ACPI reboot
    mov ax, 0x5307
    mov bx, 0x0001
    mov cx, 0x0001
    int 0x15
    ret


