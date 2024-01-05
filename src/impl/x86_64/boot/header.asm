section .multiboot_header
header_start:
    dd 0xe85250d6 ; multiboot2
    ; architecture
    dd 0 ; i386 protected mode 
    ; header length
    dd header_end - header_start
    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + header_end - header_start)
    ;end
    dw 0
    dw 0
    dd 8
header_end: